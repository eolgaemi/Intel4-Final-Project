/*
 * wifiCom.c
 *
 *  Created on: Aug 31, 2024
 *      Author: IOT
 */
#include "wifiCom.h"

static char ip_addr[16];
static char response[MAX_ESP_RX_BUFFER];

//==================uart6=========================
extern volatile unsigned char rx2Flag;
extern volatile char rx2Data[50];
extern uint8_t cdata;
cb_data_t cb_data;
char strBuff[MAX_ESP_COMMAND_LEN];

static uint8_t data;
extern UART_HandleTypeDef huart6;
extern UART_HandleTypeDef huart2;

static int esp_reset(void);

void wifiCom_Init(void){
	memset(ip_addr,0x00,sizeof(ip_addr));
	HAL_UART_Receive_IT(&huart6, &data, 1);
	AiotClient_Init();
	printf("Wi-Fi Communication Initialized...\n");
	//wifi_app();
	drv_esp_test_command();
	//printf("Wi-Fi Communication Initialize Failed...\n");
}

static int esp_at_command(uint8_t *cmd, uint8_t *resp, uint16_t *length, int16_t time_out)
/*
 1) cmd     : AT Command buffer
 2) resp    : response buffer from esp01
 3) length  : length of response from esp01
 4) time_out: time out
*/
{
	//initialize
    *length = 0;
    memset(resp, 0x00, MAX_UART_RX_BUFFER);
    memset(&cb_data, 0x00, sizeof(cb_data_t));

    //Transmit CMD to UART6
    if(HAL_UART_Transmit(&huart6, cmd, strlen((char *)cmd), 0xffff) != HAL_OK)
        return -1;

    // until time_out > 0
    while(time_out > 0)
    {
    	// if buffer overflow
        if(cb_data.length >= MAX_UART_RX_BUFFER)
        {
        	printf("AT Command buffer overflow\n");
        	printf("Data length : %d\n",cb_data.length);
            return -2;
        }
        // if there is any error
        else if(strstr((char *)cb_data.buf, "ERROR") != NULL)
        {
        	printf("AT Command Error: %s \n",cb_data.buf);
            return -3;
        }
        // if there is any OK
        else if(strstr((char *)cb_data.buf, "OK") != NULL)
        {
        	printf("AT Command OK\n");
        	// copy cb_data to resp
            memcpy(resp, cb_data.buf, cb_data.length);
            // save length
            *length = cb_data.length;
            break;
        }
        // this function tries 10 times
        time_out -= 10;
        HAL_Delay(10);
    }
    HAL_Delay(500);
    return 0;
}

// send AT+RST command to esp
static int esp_reset(void)
{
    uint16_t length = 0;
    if(esp_at_command((uint8_t *)"AT+RST\r\n", (uint8_t *)response, &length, 1000) != 0)
    {
       return -1;
    }
    return esp_at_command((uint8_t *)"AT\r\n", (uint8_t *)response, &length, 1000);
}

// get ip addr from esp "STA Mode (Only Client)"
static int esp_get_ip_addr(uint8_t is_debug)
{
	// if ip_addr is empty
    if(strlen(ip_addr) != 0)
    {
    	// if ip_addr == 0.0.0.0
        if(strcmp(ip_addr, "0.0.0.0") == 0)
            return -1;
    }
    else
    {
        uint16_t length;
        //send AT+CIPSTA? -> get present IP Address
        if(esp_at_command((uint8_t *)"AT+CIPSTA?\r\n", (uint8_t *)response, &length, 10000) != 0)
            printf("ip_state command fail\r\n");
        else
        {
        	// saved line = AT+CIPSTA?
            char *line = strtok(response, "\r\n");

            // print every response from esp module
            if(is_debug)
            {
                for(int i = 0 ; i < length ; i++)
                    printf("%c", response[i]);
            }

            // if line is not NULL
            while(line != NULL)
            {
            	// if there is ip:
                if(strstr(line, "ip:") != NULL)
                {
                    char *ip;

                    strtok(line, "\"");
                    ip = strtok(NULL, "\"");
                    // if ip is not 0.0.0.0
                    if(strcmp(ip, "0.0.0.0") != 0)
                    {
                    	// clear ip_addr buffer & copy
                        memset(ip_addr, 0x00, sizeof(ip_addr));
                        memcpy(ip_addr, ip, strlen(ip));
                        return 0;
                    }
                }
                // if ther is no ip send "NULL\r\n"
                line = strtok(NULL, "\r\n");
            }
        }
        return -1;
    }
    return 0;
}

// get ip addr from esp "AP Mode (Server + Client)"
static int request_ip_addr(uint8_t is_debug)
{
    uint16_t length = 0;

    //send AT+CIFSR? -> get present IP Address
    if(esp_at_command((uint8_t *)"AT+CIFSR\r\n", (uint8_t *)response, &length, 1000) != 0)
        printf("request ip_addr command fail\r\n");
    else
    {
        char *line = strtok(response, "\r\n");

        if(is_debug)
        {
            for(int i = 0 ; i < length ; i++)
                printf("%c", response[i]);
        }

        while(line != NULL)
        {
            if(strstr(line, "CIFSR:STAIP") != NULL)
            {
                char *ip;

                strtok(line, "\"");
                ip = strtok(NULL, "\"");
                if(strcmp(ip, "0.0.0.0") != 0)
                {
                    memset(ip_addr, 0x00, sizeof(ip_addr));
                    memcpy(ip_addr, ip, strlen(ip));
                    return 0;
                }
            }
            line = strtok(NULL, "\r\n");
        }
    }

    return -1;
}

// connect as a client
int esp_client_conn()
{
	char at_cmd[MAX_ESP_COMMAND_LEN] = {0, };
	uint16_t length = 0;

	// make cmd to connect remote server
	sprintf(at_cmd,"AT+CIPSTART=\"TCP\",\"%s\",%d\r\n",SERVER_IP,SERVER_PORT);
	esp_at_command((uint8_t *)at_cmd,(uint8_t *)response, &length, 1000);					//CONNECT
	esp_send_data("["LOGID":"PASSWD"]");
	return 0;
}

// try esp reset with at command
void reset_func()
{
	printf("esp reset... ");
	if(esp_reset() == 0)
			printf("OK\r\n");
	else
			printf("fail\r\n");
}

// try to get esp firmware version
void version_func()
{
  uint16_t length = 0;
  printf("esp firmware version\r\n");
  if(esp_at_command((uint8_t *)"AT+GMR\r\n", (uint8_t *)response, &length, 1000) != 0)
      printf("ap scan command fail\r\n");
  else
  {
      for(int i = 0 ; i < length ; i++)
          printf("%c", response[i]);
  }
}

// try to make connetion with AP through STA mode
void ap_conn_func(char *ssid, char *passwd)
{
  uint16_t length = 0;
  char at_cmd[MAX_ESP_COMMAND_LEN] = {0, };
  if(ssid == NULL || passwd == NULL)
  {
      printf("invalid command : ap_conn <ssid> <passwd>\r\n");
      return;
  }

  // clear memory & save commands
  memset(at_cmd, 0x00, sizeof(at_cmd));
  sprintf(at_cmd, "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid,passwd);
  printf("%s\n",at_cmd);
  if(esp_at_command((uint8_t *)at_cmd, (uint8_t *)response, &length, 6000) != 0)
      printf("ap scan command fail\r\n");
  else
  {
	  printf("%s\n",response);
	  for(int i = 0 ; i < length ; i++)
		  printf("%c", response[i]);
  }
}

// Return accessed AP info
void ip_state_func()
{
  uint16_t length = 0;
  if(esp_at_command((uint8_t *)"AT+CWJAP?\r\n", (uint8_t *)response, &length, 1000) != 0)
      printf("ap connected info command fail\r\n");
  else
  {
      for(int i = 0 ; i < length ; i++)
          printf("%c", response[i]);
  }
  printf("\r\n");

  //get ip addr with STA mode
  if(esp_get_ip_addr(1) == 0)
      printf("ip_addr = [%s]\r\n", ip_addr);
}

int drv_esp_test_command(void)
{
    char command[MAX_UART_COMMAND_LEN];
    uint16_t length = 0;

	// print prompt
	drv_uart_tx_buffer((uint8_t *)"esp>", 4);

    while(1)
    {
		// clear command buffer
        memset(command, 0x00, sizeof(command));

		if(drv_uart_rx_buffer((uint8_t *)command, MAX_UART_COMMAND_LEN) == 0)
			continue;

		printf("received command : %s\n",command);

        if(strcmp(command, "help") == 0)
        {
            printf("============================================================\r\n");
            printf("* help                    : help\r\n");
            printf("* quit                    : esp test exit\r\n");
            printf("* reset                   : esp restart\r\n");
            printf("* version                 : esp firmware version\r\n");
            printf("* ap_scan                 : scan ap list\r\n");
            printf("* ap_conn <ssid> <passwd> : connect ap & obtain ip addr\r\n");
            printf("* ap_disconnect           : disconnect ap\r\n");
            printf("* ip_state                : display ip addr\r\n");
            printf("* request_ip              : obtain ip address\r\n");
            printf("* AT+<XXXX>               : AT COMMAND\r\n");
            printf("*\r\n");
            printf("* More <AT COMMAND> information is available on the following website\r\n");
            printf("*  - https://docs.espressif.com/projects/esp-at/en/latest/AT_Command_Set\r\n");
            printf("============================================================\r\n");
        	// print prompt
        	drv_uart_tx_buffer((uint8_t *)"esp>", 4);
        }
        else if(strcmp(command, "quit") == 0)
        {
            printf("esp test exit\r\n");
            break;
        }
        else if(strcmp(command, "reset") == 0)
        {
        		reset_func();
        		// print prompt
        		drv_uart_tx_buffer((uint8_t *)"esp>", 4);

        }
        else if(strcmp(command, "version") == 0)
        {
        		version_func();
        		// print prompt
        		drv_uart_tx_buffer((uint8_t *)"esp>", 4);
        }
        else if(strcmp(command, "ap_scan") == 0)
        {
            printf("ap scan...\r\n");
            if(esp_at_command((uint8_t *)"AT+CWLAP\r\n", (uint8_t *)response, &length, 5000) != 0)
                printf("ap scan command fail\r\n");
            else
            {
                for(int i = 0 ; i < length ; i++)
                    printf("%c", response[i]);
            }
        	// print prompt
        	drv_uart_tx_buffer((uint8_t *)"esp>", 4);
        }
        else if(strncmp(command, "ap_conn", strlen("ap_conn")) == 0)
        {
        		ap_conn_func(SSID,PASS);
        		// print prompt
        		drv_uart_tx_buffer((uint8_t *)"esp>", 4);
        }
        else if(strcmp(command, "ap_disconnect") == 0)
        {
            if(esp_at_command((uint8_t *)"AT+CWQAP\r\n", (uint8_t *)response, &length, 1000) != 0)
                printf("ap connected info command fail\r\n");
            else
            {
                for(int i = 0 ; i < length ; i++)
                    printf("%c", response[i]);

                memset(ip_addr, 0x00, sizeof(ip_addr));
            }
        	// print prompt
        	drv_uart_tx_buffer((uint8_t *)"esp>", 4);
        }
        else if(strcmp(command, "ip_state") == 0)
        {
        		ip_state_func();
        		// print prompt
        		drv_uart_tx_buffer((uint8_t *)"esp>", 4);
        }
        else if(strcmp(command, "request_ip") == 0)
        {
            request_ip_addr(1);
        	// print prompt
        	drv_uart_tx_buffer((uint8_t *)"esp>", 4);
        }
        else if(strncmp(command, "AT+", 3) == 0)
        {
            uint8_t at_cmd[MAX_UART_COMMAND_LEN+3];

            memset(at_cmd, 0x00, sizeof(at_cmd));
            sprintf((char *)at_cmd, "%s\r\n", command);
            if(esp_at_command(at_cmd, (uint8_t *)response, &length, 1000) != 0)
                printf("AT+ command fail\r\n");
            else
            {
                for(int i = 0 ; i < length ; i++)
                    printf("%c", response[i]);
            }
        	// print prompt
        	drv_uart_tx_buffer((uint8_t *)"esp>", 4);
        }
        else
        {
            printf("unkwon command\r\n");
        	// print prompt
        	drv_uart_tx_buffer((uint8_t *)"esp>", 4);
        }
    }

    return 0;
}

void USART6_RxCpltHandler(UART_HandleTypeDef *huart)
{
	if(cb_data.length < MAX_ESP_RX_BUFFER)
	{
		cb_data.buf[cb_data.length++] = data;
	}
	HAL_UART_Receive_IT(huart, &data, 1);
}

void AiotClient_Init(void)
{
	reset_func();
	version_func(); 		// AP func
	ap_conn_func(SSID,PASS);
	//start_esp_server();		// AP func
	//ip_state_func();		// AP func
	//request_ip_addr(1);
	esp_client_conn();
	//ip_state_func();		// AP func
}

void esp_send_data(char *data)
{
	char at_cmd[MAX_ESP_COMMAND_LEN] = {0, };
    uint16_t length = 0;
	sprintf(at_cmd,"AT+CIPSEND=%d\r\n",strlen(data));
	if(esp_at_command((uint8_t *)at_cmd,(uint8_t *)response, &length, 10000) == 0)
	{
			esp_at_command((uint8_t *)data,(uint8_t *)response, &length, 10000);
	}
}

int drv_uart_tx_buffer(uint8_t *buf, uint16_t size)
{
    if(HAL_UART_Transmit(&huart2, buf, size, 100) != HAL_OK)
        return -1;

    return 0;
}

int drv_uart_rx_buffer(uint8_t *buf, uint16_t size)
{
    uint16_t i = 0;
    uint32_t timeout = HAL_GetTick() + 1000; // 1초 타임아웃 설정

    // 수신된 데이터가 있을 때까지 대기합니다.
    while (i < size)
    {
        if (HAL_GetTick() > timeout) // 타임아웃 체크
        {
            return 0; // 타임아웃 발생 시 0을 반환
        }

        if (rx2Flag) // UART2에서 수신된 데이터가 있음을 나타냄
        {
            if (rx2Data[i] != '\n' && rx2Data[i] != '\r') // '\n'과 '\r'을 무시
            {
                buf[i] = rx2Data[i]; // 수신된 데이터를 버퍼에 저장
                i++; // 인덱스를 증가시킴
            }

            if (rx2Data[i-1] == '\0') // null-terminator를 확인하여 중지
                break;
        }
    }

    if (i == 0) // 수신된 데이터가 없는 경우
    {
        return 0;
    }

    // 수신된 데이터를 다 복사했으므로, rx2Data 초기화
    for (int i = 0; i < sizeof(rx2Data); i++) {
        rx2Data[i] = 0;
    }

    // 플래그 초기화
    rx2Flag = 0;

    return i; // 수신된 바이트 수를 반환
}

void wifi_app(void){
	while(1){
		if(strstr((char *)cb_data.buf,"+IPD") && cb_data.buf[cb_data.length-1] == '\n')
			{
				//수신포멧  \r\n+IPD,15:[KSH_LIN]HELLO\n
				strcpy(strBuff,strchr((char *)cb_data.buf,'['));
				memset(cb_data.buf,0x0,sizeof(cb_data.buf));
				cb_data.length = 0;
				esp_event(strBuff);
			}
			if(rx2Flag)
			{
				printf("recv2 : %s\r\n",rx2Data);
				rx2Flag =0;
			}
	}
}

///
void esp_event(char * recvBuf)
{

}
//*/

/*//
void esp_event(char * recvBuf)
{
  int i=0;
  char * pToken;
  char * pArray[ARR_CNT]={0};
  char sendBuf[MAX_UART_COMMAND_LEN]={0};

  strBuff[strlen(recvBuf)-1] = '\0';	//'\n' cut
  printf("\r\nDebug recv : %s\r\n",recvBuf);

  pToken = strtok(recvBuf,"[@]");
  while(pToken != NULL)
  {
    pArray[i] = pToken;
    if(++i >= ARR_CNT)
      break;
    pToken = strtok(NULL,"[@]");
  }

  if(!strcmp(pArray[1],"LED"))
  {
  	if(!strcmp(pArray[2],"ON"))
  	{
  		MX_GPIO_LED_ON(LD2_Pin);

  	}
		else if(!strcmp(pArray[2],"OFF"))
		{
				MX_GPIO_LED_OFF(LD2_Pin);
		}
		sprintf(sendBuf,"[%s]%s@%s\n",pArray[0],pArray[1],pArray[2]);
  }
  else if(!strncmp(pArray[1]," New conn",8))
  {
//	   printf("Debug : %s, %s\r\n",pArray[0],pArray[1]);
     return;
  }
  else if(!strncmp(pArray[1]," Already log",8))
  {
// 	    printf("Debug : %s, %s\r\n",pArray[0],pArray[1]);
			esp_client_conn();
      return;
  }
  else
      return;

  esp_send_data(sendBuf);
  printf("Debug send : %s\r\n",sendBuf);
}
//*/
