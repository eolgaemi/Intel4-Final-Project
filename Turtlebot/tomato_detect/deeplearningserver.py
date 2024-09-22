import cv2
import numpy as np
import tensorflow as tf
from tensorflow.keras.models import load_model
from ultralytics import YOLO
import socket

client_socket = None

def client_initialize():
    global client_socket     

	# 서버 정보 설정
    host = '10.42.0.1'  # 서버 IP
    port = 5000         # 서버 포트
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        # 서버에 연결
        client_socket.connect((host, port))
        print(f'{host}:{port}에 연결되었습니다.')

        # 1. 첫 번째 메시지 전송: [STF_BOT:PASSWD]
        initial_message = '[STF_BOT:PASSWD]'
        client_socket.sendall(initial_message.encode('utf-8'))
        print(f'첫 번째 메시지 전송: {initial_message}')

    except Exception as e:
        print(f'오류가 발생했습니다: {e}')        
	

def send_message(pot, leaf_status, tomato_status):

    # 2. 두 번째 동적으로 생성된 메시지 전송
    try:
        # pot 값이 1, 2, 3 중 하나일 때 POT1, POT2, POT3으로 변환
        pot_str = f'POT{pot}' if pot in [1, 2, 3] else 'Unknown'        
        message = f'[STF_SQL]{pot_str}@Leaf@{leaf_status}@Tomato@{tomato_status}'
        print(f'보낼 메시지: {message}')
        
        client_socket.sendall(message.encode('utf-8'))
        print('동적으로 생성된 메시지를 성공적으로 보냈습니다.')

    except Exception as e:
        print(f'오류가 발생했습니다: {e}')

def detect_ripe_tomatoes(cropped_img, model):

    ripe_found = False
    # HSV 색상으로 변환
    hsv = cv2.cvtColor(cropped_img, cv2.COLOR_BGR2HSV)

    # 빨간색 토마토 범위 설정
    lower_red = np.array([0, 100, 100])
    upper_red = np.array([10, 255, 255])

    # 마스크 생성
    mask = cv2.inRange(hsv, lower_red, upper_red)

    # 윤곽선 찾기
    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    for contour in contours:
        area = cv2.contourArea(contour)

        if area > 300:
            x, y, w, h = cv2.boundingRect(contour)
            tomato = cropped_img[y:y+h, x:x+w]
            tomato = cv2.resize(tomato, (224, 224))
            tomato = tomato / 255.0
            tomato = np.expand_dims(tomato, axis=0)

            prediction = model.predict(tomato)[0][0]
            if prediction > 0.5:
                label = "Ripe"
                ripe_found = True                 
            else:
                label = "Unripe"                

            color = (0, 0, 255) if label == "Ripe" else (0, 255, 0)

            cv2.rectangle(cropped_img, (x, y), (x + w, y + h), color, 2)
            cv2.putText(cropped_img, label, (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, color, 2)
    return ripe_found

def start_server(host='0.0.0.0', port=5000):
    global client_socket
    conf_threshold = 0.6
    
    # TCP 소켓 생성
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(1)
    confidence_threshold = 0.6 # YOLOv8 신뢰도 임계값 설정
    print("서버가 포트에서 대기 중:", port)

    # 모델 로드
    detection_model = YOLO('leaf_float32.tflite')

    # 학습한 토마토 잎 병 진단 모델 및 익은 토마토 감지 모델 로드
    leaf_disease_model = load_model('./tomato_leaf_disease.h5')
    tomato_model = load_model('tomato_model.h5')
    print("모델 로드 완료.")

    # 딥러닝 모델 입력 크기
    target_size = (256, 256)

    # 객체 클래스 및 레이블 정의
    object_class = ["leaf", "tomato"]
    #leaf_labels = ["Bacterial_spot", 
    class_labels = ["Bacterial_spot",     
                   "Early_blight", 
                   "Late_blight", 
                   "Leaf_Mold", 
                   "Septoria_leaf_spot", 
                "Spider_mites", 
                "Target_Spot", 
                "Yellow_Leaf_Curl_Virus", 
                "Tomato_mosaic_virus", 
                "Healthy"]

    tomato_labels = [
        "Healthy",
        "Diseased1",
        "Diseased2"  # 토마토에 대한 추가 클래스 레이블
    ]

    # 클라이언트 연결 수신
    conn, addr = server_socket.accept()
    print("연결된 클라이언트:", addr)

    while True:

        # arcnum 수신
        arcnum_data = conn.recv(4)  
        arcnum = int.from_bytes(arcnum_data, byteorder='big')    
        print(f"Received arcnum: {arcnum}")

        # 수신 데이터 크기 수신
        data_size = conn.recv(4)
        if not data_size:
            print("데이터를 수신하지 못했습니다. 연결 종료.")
            break

        # 데이터 크기를 바이트에서 정수로 변환
        data_size = int.from_bytes(data_size, byteorder='big')
        print("기대되는 데이터 크기:", data_size)

        # 실제 데이터 수신
        data = b''
        while len(data) < data_size:
            packet = conn.recv(4096)
            if not packet:
                print("패킷을 수신하지 못했습니다. 연결 종료.")
                break
            data += packet

        # 수신한 데이터를 NumPy 배열로 변환하고 이미지를 디코딩
        np_data = np.frombuffer(data, np.uint8)
        frame = cv2.imdecode(np_data, cv2.IMREAD_COLOR)

        # 수신한 이미지가 유효할 경우 처리
        if frame is not None and frame.size > 0:
            
            message = "0"  # 기본 메시지            
#            cv2.imshow('Received Image', frame)  # 수신한 이미지 표시

            # 익은 토마토 감지
            is_ripe = detect_ripe_tomatoes(frame, tomato_model)

            # YOLOv8로 잎 감지
            results = detection_model.predict(frame, imgsz=(480, 480), conf=conf_threshold)

            for result in results[0].boxes:
                x1, y1, x2, y2 = map(int, result.xyxy[0])
                conf = result.conf[0]
                
                cropped_img = frame[y1:y2, x1:x2]
                resized_img = cv2.resize(cropped_img, target_size)
                input_img = np.expand_dims(resized_img, axis=0) / 255.0

                # 병 진단 예측
                predictions = leaf_disease_model.predict(input_img)
                predicted_class = np.argmax(predictions[0])
                predicted_label = class_labels[predicted_class]

                if is_ripe:
                    send_message(arcnum, predicted_label, "Ripe") 
                else:
                    send_message(arcnum, predicted_label, None) 

                # 바운딩 박스 및 라벨 표시
                cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
                cv2.putText(frame, f'{predicted_label}: {conf:.2f}', (x1, y1 - 10), 
                            cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0, 255, 0), 2)                         
                

            # 영상 출력
            cv2.imshow('Detection', frame)

            # 객체 탐지 수행

            # 클라이언트에게 응답 메시지 전송
            message_bytes = message.encode('utf-8')
            conn.sendall(len(message_bytes).to_bytes(4, 'big'))  # 메시지 크기 전송
            conn.sendall(message_bytes)  # 실제 메시지 전송
            print(f"전송한 메시지: {message}")

            # 'q' 키가 눌리면 종료
            if cv2.waitKey(1) & 0xFF == ord('q'):
                print("종료 중...")
                break
        else:
            print("이미지를 디코딩하는 데 실패했습니다.")

    # 리소스 정리
    conn.close()
    server_socket.close()
    client_socket.close()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    start_server()
    client_initialize() # 서버 접속
