# 컴파일러 설정
CC = gcc
CFLAGS = -Wall -pthread

# 타겟 실행 파일 이름
TARGET = iot_client

# 소스 파일 목록
SRCS = iot_client_cbf.c callback_example.c

# 오브젝트 파일 목록
OBJS = $(SRCS:.c=.o)

# 헤더 파일 목록
HDRS = iot_client_cbf.h callback_example.h

# 기본 타겟
all: $(TARGET)

# 타겟을 컴파일하는 규칙
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 오브젝트 파일을 만드는 규칙
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c -o $@ $<

# 정리 규칙
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

