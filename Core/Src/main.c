/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file          : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
FATFS fs;
FIL fil;
#define CAN_TIMEOUT 40
CAN_TxHeaderTypeDef pHeader;
CAN_RxHeaderTypeDef pRxHeader;
CAN_FilterTypeDef sFilterConfig;
uint8_t rxData[8];

uint16_t arac_hiz=0;
uint16_t motor_temp_tam=0;
uint16_t motor_temp_on=0;
uint16_t surucu_temp_tam=0;
uint16_t surucu_temp_on=0;
float motor_temp=0;
float surucu_temp=0;
int a;
uint16_t sarj_gucu=0;
uint16_t kalan_sure=0;
uint16_t sarj_bilgisi=0;
uint16_t count1 =0;
uint16_t count2 =0;
uint32_t bms_timer = 0;
uint32_t motor_timer = 0;

uint32_t arac_hizi =0;
uint32_t hiz_ibresi =0;
char mesaj[];

float sicaklik=0;
float hucre1=0;
float hucre2=0;
float hucre3=0;
float hucre4=0;
float hucre5=0;
float hucre6=0;
float hucre7=0;
float hucre8=0;
float hucre9=0;
float hucre10=0;
float hucre11=0;
float hucre12=0;
float hucre13=0;
float hucre14=0;
float hucre15=0;
float hucre16=0;
float hucre17=0;
float hucre18=0;
float hucre19=0;
float hucre20=0;
float hucre21=0;
float hucre22=0;
float toplam_gerilim=0;
float kalan_enerj_miktari=0;

int32_t int_sicaklik=0;
int32_t int_hucre1=0;
int32_t int_hucre2=0;
int32_t int_hucre3=0;
int32_t int_hucre4=0;
int32_t int_hucre5=0;
int32_t int_hucre6=0;
int32_t int_hucre7=0;
int32_t int_hucre8=0;
int32_t int_hucre9=0;
int32_t int_hucre10=0;
int32_t int_hucre11=0;
int32_t int_hucre12=0;
int32_t int_hucre13=0;
int32_t int_hucre14=0;
int32_t int_hucre15=0;
int32_t int_hucre16=0;
int32_t int_hucre17=0;
int32_t int_hucre18=0;
int32_t int_hucre19=0;
int32_t int_hucre20=0;
int32_t int_hucre21=0;
int32_t int_hucre22=0;
int32_t int_toplam_gerilim=0;
int32_t int_kalan_enerj_miktari=0;

char motors [20];
char bataryas [20];
char arachızs [20];
char kalans [20];
char topgerilims [20];
char kalansures [20];
char sarjgucus [20];
int bat_sicaklik;
//batarya yüzdesi eksik
//arac modu
char h1s [20];
char h2s [20];
char h3s [20];
char h4s [20];
char h5s [20];
char h6s [20];
char h7s [20];
char h8s [20];
char h9s [20];
char h9s [20];
char h10s [20];
char h11s [20];
char h12s [20];
char h13s [20];
char h14s [20];
char h15s [20];
char h16s [20];
char h17s [20];
char h18s [20];
char h19s [20];
char h20s [20];
char h21s [20];
char h22s [20];

char  H1 []= "h1"  ; //Hucre 1
char  H2 []= "h2" ; //Hucre 2
char  H3 []= "h3" ; //Hucre 3
char  H4 []= "h4" ; //Hucre 4
char  H5 []= "h5" ; //Hucre 5
char  H6 []= "h6"  ; //Hucre 6
char  H7 []= "h7"  ; //Hucre 7
char  H8 []= "h8"  ; //Hucre 8
char  H9 []= "h9"  ; //Hucre 9
char  H10[]= "h10"  ; //Hucre 10
char  H11[]= "h11" ; //Hucre 11
char  H12[]= "h12"  ; //Hucre 12
char  H13[]= "h13"  ; //Hucre 13
char  H14[]= "h14"  ; //Hucre 14
char  H15[]= "h15"  ; //Hucre 15
char  H16[]= "h16" ; //Hucre 16
char  H17[]= "h17" ; //Hucre 17
char  H18[]= "h18" ; //Hucre 18
char  H19[]= "h19" ; //Hucre 19
char  H20[]= "h20" ; //Hucre 20
char  H21[]= "h21" ; //Hucre 21
char  H22[]= "h22" ; //Hucre 22


/*Tam şarja kalan süre,Batarya toplam gerilim,Kalan enerji Miktarı,�?arj gücü değişkenlerini
                  *  oluşturduk nextion parametresini anlaşılabilir olarak kullandık  */


char  tsks[]= "t61" ; //Tam şarja kalan süre
char  btg[]= "t65" 	;  //Batarya toplam gerilim
char  kem[]= "t63"	;  //Kalan enerji Miktarı
char  sg[]= "t64" 	;   //�?arj gücü
char  ms[]= "t62" 	;	  //motor sicakligi
char  bs[]= "t60" 	;	  //batarya sicakligi
char  arac_modu []= "t80" 	;

//akım okuma
uint16_t data1;
uint32_t adc_value[1];
int current;


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

CAN_HandleTypeDef hcan1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;

/* USER CODE BEGIN PV */
uint32_t hiz_ibresiderece;
uint32_t arac_hizi;
uint32_t toplam_batarya;
uint32_t batarya_sicaklik ;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_CAN1_Init(void);
static void MX_TIM2_Init(void);
static void MX_UART4_Init(void);
static void MX_UART5_Init(void);
static void MX_SPI1_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){

	if(hadc->Instance == ADC1)
		{
		//Temperature Read DMA
		data1 = adc_value[0];
		}
}
double Curr (int akim){  //Throttle Function for in While Working
	  current = akim;
	  current = current * (-0.01);
	  current = current +62-31 -1,3;
	  return current;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM2) {
	  count1++;
	  bms_timer++;
	  motor_timer++;
	  if (bms_timer > CAN_TIMEOUT) {
		  	  	int_sicaklik = 0;
		  	    int_hucre1 = 0;
		  	    int_hucre2 = 0;
		  	    int_hucre3 =0;
		  	    int_hucre4=0;
		  	    int_hucre5=0;
		  	    int_hucre6=0;
		  	    int_hucre7=0;
		  	    int_hucre8=0;
		  	    int_hucre9=0;
		  	    int_hucre10=0;
		  	    int_hucre11=0;
		  	    int_hucre12=0;
		  	    int_hucre13=0;
		  	    int_hucre14=0;
		  	    int_hucre15=0;
		  	    int_hucre16=0;
		  	    int_hucre17=0;
		        int_hucre18=0;
		  	    int_hucre19=0;
		  	    int_hucre20=0;
		  	    int_hucre21=0;
		  	    int_hucre22=0;
		  	    int_toplam_gerilim=0;
		  	    int_kalan_enerj_miktari=0;
	            sicaklik = 0;
	            hucre1 = 0;
	            hucre2 = 0;
	            hucre3 = 0;
	            hucre4 = 0;
	            hucre5 = 0;
	            hucre6 = 0;
	            hucre7 = 0;
	            hucre8 = 0;
	            hucre9 = 0;
	            hucre10 = 0;
	            hucre11 = 0;
	            hucre12 = 0;
	            hucre13 = 0;
	            hucre14 = 0;
	            hucre15 = 0;
	            hucre16 = 0;
	            hucre17 = 0;
	            hucre18 = 0;
	            hucre19 = 0;
	            hucre20 = 0;
	            hucre21 = 0;
	            hucre22 = 0;
	            toplam_gerilim = 0;
	            kalan_enerj_miktari = 0;
	        }
	  if (motor_timer > CAN_TIMEOUT) {
		        motor_temp_tam=0;
		        motor_temp_on=0;
		        surucu_temp_tam=0;
		        surucu_temp_on=0;
	            arac_hiz = 0;
	            motor_temp = 0.0f;
	            surucu_temp = 0.0f;
	          }



  }
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
 /*
   if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &pRxHeader, rxData) == HAL_OK) {


        if (pRxHeader.StdId == 0x0127) { // motor sürücü
            arac_hiz = (uint16_t)(rxData[0] | (rxData[1] << 8));
            motor_temp_tam = (uint16_t)(rxData[2] | (rxData[3] << 8));
            motor_temp_on = (uint16_t)(rxData[4] | (rxData[5] << 8));
            surucu_temp_tam = (uint16_t)(rxData[6] | (rxData[7] << 8));
            motor_temp = motor_temp_tam + (motor_temp_on / 100.0f);
            motor_timer = 0;


        }
        else if (pRxHeader.StdId == 0x0128) { // motor sürücü
            surucu_temp_on = (uint16_t)(rxData[0] | (rxData[1] << 8));
            surucu_temp = surucu_temp_tam + (surucu_temp_on / 100.0f);
            motor_timer = 0;


        }

        else if (pRxHeader.StdId == 0x0129) { // yerleşik şarj
            sarj_gucu = (uint16_t)(rxData[0] | (rxData[1] << 8));
            kalan_sure = (uint16_t)(rxData[2] | (rxData[3] << 8));
            sarj_bilgisi = (uint16_t)(rxData[4] | (rxData[5] << 8));


        }
        else if (pRxHeader.StdId == 0x0130) {  //bms
            int_sicaklik = (uint16_t)(rxData[0] | (rxData[1] << 8));
            int_hucre1 = (uint16_t)(rxData[2] | (rxData[3] << 8));
            int_hucre2 = (uint16_t)(rxData[4] | (rxData[5] << 8));
            int_hucre3 = (uint16_t)(rxData[6] | (rxData[7] << 8));

            sicaklik = (int_sicaklik / 1000.0f);
            bat_sicaklik= int_sicaklik/1000;
            hucre1 = (int_hucre1 / 10000.0f);
            hucre2 = (int_hucre2 / 10000.0f);
            hucre3 = (int_hucre3 / 10000.0f);
            bms_timer = 0;


        }
        else if (pRxHeader.StdId == 0x0131) {
            int_hucre4 = (uint16_t)(rxData[0] | (rxData[1] << 8));
            int_hucre5 = (uint16_t)(rxData[2] | (rxData[3] << 8));
            int_hucre6 = (uint16_t)(rxData[4] | (rxData[5] << 8));
            int_hucre7 = (uint16_t)(rxData[6] | (rxData[7] << 8));

            hucre4 = (int_hucre4 / 10000.0f);
            hucre5 = (int_hucre5 / 10000.0f);
            hucre6 = (int_hucre6 / 10000.0f);
            hucre7 = (int_hucre7 / 10000.0f);
            bms_timer = 0;


        }
        else if (pRxHeader.StdId == 0x0132) {
            int_hucre8 = (uint16_t)(rxData[0] | (rxData[1] << 8));
            int_hucre9 = (uint16_t)(rxData[2] | (rxData[3] << 8));
            int_hucre10 = (uint16_t)(rxData[4] | (rxData[5] << 8));
            int_hucre11 = (uint16_t)(rxData[6] | (rxData[7] << 8));

            hucre8 = (int_hucre8 / 10000.0f);
            hucre9 = (int_hucre9 / 10000.0f);
            hucre10 = (int_hucre10 / 10000.0f);
            hucre11 = (int_hucre11 / 10000.0f);
            bms_timer = 0;



        }
        else if (pRxHeader.StdId == 0x0133) {
            int_hucre12 = (uint16_t)(rxData[0] | (rxData[1] << 8));
            int_hucre13 = (uint16_t)(rxData[2] | (rxData[3] << 8));
            int_hucre14 = (uint16_t)(rxData[4] | (rxData[5] << 8));
            int_hucre15 = (uint16_t)(rxData[6] | (rxData[7] << 8));

            hucre12 = (int_hucre12 / 10000.0f);
            hucre13 = (int_hucre13 / 10000.0f);
            hucre14 = (int_hucre14 / 10000.0f);
            hucre15 = (int_hucre15 / 10000.0f);
            bms_timer = 0;


        }
        else if (pRxHeader.StdId == 0x0134) {
            int_hucre16 = (uint16_t)(rxData[0] | (rxData[1] << 8));
            int_hucre17 = (uint16_t)(rxData[2] | (rxData[3] << 8));
            int_hucre18 = (uint16_t)(rxData[4] | (rxData[5] << 8));
            int_hucre19 = (uint16_t)(rxData[6] | (rxData[7] << 8));

            hucre16 = (int_hucre16 / 10000.0f);
            hucre17 = (int_hucre17 / 10000.0f);
            hucre18 = (int_hucre18 / 10000.0f);
            hucre19 = (int_hucre19 / 10000.0f);
            bms_timer = 0;



        }
        else if (pRxHeader.StdId == 0x0135) {
            int_hucre20 = (uint16_t)(rxData[0] | (rxData[1] << 8));
            int_hucre21 = (uint16_t)(rxData[2] | (rxData[3] << 8));
            int_hucre22 = (uint16_t)(rxData[4] | (rxData[5] << 8));
            int_toplam_gerilim = (uint16_t)(rxData[6] | (rxData[7] << 8));

            hucre20 = (int_hucre20 / 10000.0f);
            hucre21 = (int_hucre21 / 10000.0f);
            hucre22 = (int_hucre22 / 10000.0f);
            toplam_gerilim = (int_toplam_gerilim / 100.0f);

            bms_timer = 0;

        }
        else if (pRxHeader.StdId == 0x0136) {
            int_kalan_enerj_miktari = (uint16_t)(rxData[0] | (rxData[1] << 8));
            kalan_enerj_miktari = (int_kalan_enerj_miktari / 100.0f);
            bms_timer = 0;

        }

    return;
    }

}*/
	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &pRxHeader, rxData) == HAL_OK) {
	        if (pRxHeader.StdId == 0x0127 || pRxHeader.StdId == 0x0128) {
	            // motor sürücü verileri alındı
	            motor_timer = 0; // Zamanlayıcıyı sıfırla


	            if (pRxHeader.StdId == 0x0127) {
	                arac_hiz = (uint16_t)(rxData[0] | (rxData[1] << 8));
	                motor_temp_tam = (uint16_t)(rxData[2] | (rxData[3] << 8));
	                motor_temp_on = (uint16_t)(rxData[4] | (rxData[5] << 8));
	                surucu_temp_tam = (uint16_t)(rxData[6] | (rxData[7] << 8));
	                motor_temp = motor_temp_tam + (motor_temp_on / 100.0f);
	            } else if (pRxHeader.StdId == 0x0128) {
	                surucu_temp_on = (uint16_t)(rxData[0] | (rxData[1] << 8));
	                surucu_temp = surucu_temp_tam + (surucu_temp_on / 100.0f);
	            }
	        }
	        else if (pRxHeader.StdId >= 0x0130 && pRxHeader.StdId <= 0x0136) {
	            // BMS verileri alındı
	            bms_timer = 0; // Zamanlayıcıyı sıfırla


	            if (pRxHeader.StdId == 0x0130) {
	            	int_sicaklik = (uint16_t)(rxData[0] | (rxData[1] << 8));//bu kısım değişti
	                int_hucre1 = (uint16_t)(rxData[2] | (rxData[3] << 8));
	                int_hucre2 = (uint16_t)(rxData[4] | (rxData[5] << 8));
	                int_hucre3 = (uint16_t)(rxData[6] | (rxData[7] << 8));
	                sicaklik = (int_sicaklik / 1000.0f);
	                bat_sicaklik = int_sicaklik / 1000;
	                hucre1 = (int_hucre1 / 10000.0f);
	                hucre2 = (int_hucre2 / 10000.0f);
	                hucre3 = (int_hucre3 / 10000.0f);
	            } else if (pRxHeader.StdId == 0x0131) {
	                int_hucre4 = (uint16_t)(rxData[0] | (rxData[1] << 8));
	                int_hucre5 = (uint16_t)(rxData[2] | (rxData[3] << 8));
	                int_hucre6 = (uint16_t)(rxData[4] | (rxData[5] << 8));
	                int_hucre7 = (uint16_t)(rxData[6] | (rxData[7] << 8));
	                hucre4 = (int_hucre4 / 10000.0f);
	                hucre5 = (int_hucre5 / 10000.0f);
	                hucre6 = (int_hucre6 / 10000.0f);
	                hucre7 = (int_hucre7 / 10000.0f);
	            } else if (pRxHeader.StdId == 0x0132) {
	                int_hucre8 = (uint16_t)(rxData[0] | (rxData[1] << 8));
	                int_hucre9 = (uint16_t)(rxData[2] | (rxData[3] << 8));
	                int_hucre10 = (uint16_t)(rxData[4] | (rxData[5] << 8));
	                int_hucre11 = (uint16_t)(rxData[6] | (rxData[7] << 8));
	                hucre8 = (int_hucre8 / 10000.0f);
	                hucre9 = (int_hucre9 / 10000.0f);
	                hucre10 = (int_hucre10 / 10000.0f);
	                hucre11 = (int_hucre11 / 10000.0f);
	            } else if (pRxHeader.StdId == 0x0133) {
	                int_hucre12 = (uint16_t)(rxData[0] | (rxData[1] << 8));
	                int_hucre13 = (uint16_t)(rxData[2] | (rxData[3] << 8));
	                int_hucre14 = (uint16_t)(rxData[4] | (rxData[5] << 8));
	                int_hucre15 = (uint16_t)(rxData[6] | (rxData[7] << 8));
	                hucre12 = (int_hucre12 / 10000.0f);
	                hucre13 = (int_hucre13 / 10000.0f);
	                hucre14 = (int_hucre14 / 10000.0f);
	                hucre15 = (int_hucre15 / 10000.0f);
	            } else if (pRxHeader.StdId == 0x0134) {
	                int_hucre16 = (uint16_t)(rxData[0] | (rxData[1] << 8));
	                int_hucre17 = (uint16_t)(rxData[2] | (rxData[3] << 8));
	                int_hucre18 = (uint16_t)(rxData[4] | (rxData[5] << 8));
	                int_hucre19 = (uint16_t)(rxData[6] | (rxData[7] << 8));
	                hucre16 = (int_hucre16 / 10000.0f);
	                hucre17 = (int_hucre17 / 10000.0f);
	                hucre18 = (int_hucre18 / 10000.0f);
	                hucre19 = (int_hucre19 / 10000.0f);
	            } else if (pRxHeader.StdId == 0x0135) {
	                int_hucre20 = (uint16_t)(rxData[0] | (rxData[1] << 8));
	                int_hucre21 = (uint16_t)(rxData[2] | (rxData[3] << 8));
	                int_hucre22 = (uint16_t)(rxData[4] | (rxData[5] << 8));
	                int_toplam_gerilim = (uint16_t)(rxData[6] | (rxData[7] << 8));
	                hucre20 = (int_hucre20 / 10000.0f);
	                hucre21 = (int_hucre21 / 10000.0f);
	                hucre22 = (int_hucre22 / 10000.0f);
	                toplam_gerilim = (int_toplam_gerilim / 100.0f);
	            } else if (pRxHeader.StdId == 0x0136) {
	                int_kalan_enerj_miktari = (uint16_t)(rxData[0] | (rxData[1] << 8));
	                kalan_enerj_miktari = (int_kalan_enerj_miktari / 100.0f);
	            }
	        }


	        return;
	    }
	}




void LORA_SendString (char *string)
{
	char buf[100]; // göndereceğimiz mesajın boyutu
	int len= sprintf(buf,"%s",string); // hangi bloğun içine yollacaksak onun txt sini yazıyoruz
	HAL_UART_Transmit(&huart5,(uint8_t *)buf,len,1000); //mesajımızı göndermek için(sol kısım)
}



uint8_t Cmd_End[3] = {0xFF,0xFF,0xFF}; //gönderileriminizin en sondaki 3 basamağı
void NEXTION_SendString (char *ID,char *string)
{
	char buf[50]; // göndereceğimiz mesajın boyutu
	int len= sprintf(buf,"%s.txt=\"%s\"",ID,string); // hangi bloğun içine yollacaksak onun txt sini yazıyoruz
	HAL_UART_Transmit(&huart4,(uint8_t *)buf,len,1000); //mesajımızı göndermek için(sol kısım)
	HAL_UART_Transmit(&huart4,Cmd_End,3,100); // 3 elemanlı yazımızın geri kalan sağ kısmı için
}
void NEXTION_SendNum(char *obj,int32_t num)
{
	uint8_t *buffer=malloc(30*sizeof(char));
	int len =sprintf((char *)buffer,"%s.val=%d",obj,num); //göndereceğimiz derin sayısal değerlerini ve diğer parametleri yazıyoruz
	HAL_UART_Transmit(&huart4,buffer,len,1000);
	HAL_UART_Transmit(&huart4,Cmd_End,3,100);
	free(buffer);
}
void SendtoPB(char *obj,uint16_t value)
{
	char buf[30];
	int len=sprintf(buf,"%s=%u",obj,value);
	HAL_UART_Transmit(&huart4,(uint8_t *)buf,len,1000);
	HAL_UART_Transmit(&huart4,Cmd_End,3,1000);

}





/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_CAN1_Init();
  MX_TIM2_Init();
  MX_UART4_Init();
  MX_UART5_Init();
  MX_SPI1_Init();
  MX_FATFS_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */

    sFilterConfig.FilterActivation= ENABLE;
    sFilterConfig.FilterBank=0;
    sFilterConfig.FilterFIFOAssignment=CAN_FILTER_FIFO0;
    sFilterConfig.FilterIdHigh=0x0000;
    sFilterConfig.FilterIdLow=0x0000;
    sFilterConfig.FilterMaskIdHigh=(0x0130 << 5);
    sFilterConfig.FilterMaskIdLow=0x0000;
    sFilterConfig.FilterMode=CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale=CAN_FILTERSCALE_32BIT;
    HAL_CAN_ConfigFilter(&hcan1,&sFilterConfig);
    HAL_CAN_Start(&hcan1);
    //interrupt
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);

    HAL_TIM_Base_Start_IT(&htim2);

    HAL_ADC_Start_DMA(&hadc1, adc_value, 1); // ADC with DMA Start
    a=1;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */



while (1)
{
	if(a=1){
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET); // LED'i yak
	}
	current = Curr(adc_value[0]);

	/*if (current >= 1)
			 {

		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET); // LED'i yak
		NEXTION_SendString(&arac_modu,"Sarj");  //Araç modu
		HAL_Delay(1);

	}
	else {
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);
		NEXTION_SendString(&arac_modu,"Surus");  //Araç modu
		HAL_Delay(1);

	}*/
	char result[120];
		//    sprintf(result, "STM32 Test %d\n", i);
		    sprintf(result, "%lu,%d,%d,%d,%d\n", HAL_GetTick(), arac_hiz, bat_sicaklik, (int)toplam_gerilim, (int)toplam_gerilim);
		HAL_Delay(500);
		  f_mount(&fs, "", 0);
		  f_open(&fil, "write.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
		  f_lseek(&fil, f_size(&fil));
		  f_puts(result, &fil);
		  f_close(&fil);


		 sprintf(motors,"%d",motor_temp_tam);//motor temp
		 sprintf(bataryas,"%d",int_sicaklik);//batarya temp
		 sprintf(arachızs,"%d",arac_hiz);//arac hızı
		 sprintf(kalans,"%d",int_kalan_enerj_miktari/100);//kalan enerji miktarı
		 sprintf(topgerilims,"%d",int_toplam_gerilim/100);//toplam gerilim
		 sprintf(kalansures,"%d",kalan_sure);//kalan sure
		 sprintf(sarjgucus,"%d",sarj_gucu);//sarj gücü

		 //batarya yüzdesi eksik


		 sprintf(h1s,"%d.%d",int_hucre1/10000,int_hucre1%10000);
		 sprintf(h2s,"%d.%d",int_hucre2/10000,int_hucre2%10000);
		 sprintf(h3s,"%d.%d",int_hucre3/10000,int_hucre3%10000);
		 sprintf(h4s,"%d.%d",int_hucre4/10000,int_hucre4%10000);
		 sprintf(h5s,"%d.%d",int_hucre5/10000,int_hucre5%10000);
		 sprintf(h6s,"%d.%d",int_hucre6/10000,int_hucre6%10000);
		 sprintf(h7s,"%d.%d",int_hucre7/10000,int_hucre7%10000);
		 sprintf(h8s,"%d.%d",int_hucre8/10000,int_hucre8%10000);
		 sprintf(h9s,"%d.%d",int_hucre9/10000,int_hucre9%10000);
		 sprintf(h10s,"%d.%d",int_hucre10/10000,int_hucre10%10000);
		 sprintf(h11s,"%d.%d",int_hucre11/10000,int_hucre11%10000);
		 sprintf(h12s,"%d.%d",int_hucre12/10000,int_hucre12%10000);
		 sprintf(h13s,"%d.%d",int_hucre13/10000,int_hucre13%10000);
		 sprintf(h14s,"%d.%d",int_hucre14/10000,int_hucre14%10000);
		 sprintf(h15s,"%d.%d",int_hucre15/10000,int_hucre15%10000);
		 sprintf(h16s,"%d.%d",int_hucre16/10000,int_hucre16%10000);
		 sprintf(h17s,"%d.%d",int_hucre17/10000,int_hucre17%10000);
		 sprintf(h18s,"%d.%d",int_hucre18/10000,int_hucre18%10000);
		 sprintf(h19s,"%d.%d",int_hucre19/10000,int_hucre19%10000);
		 sprintf(h20s,"%d.%d",int_hucre20/10000,int_hucre20%10000);
		 sprintf(h21s,"%d.%d",int_hucre21/10000,int_hucre21%10000);
		 sprintf(h22s,"%d.%d",int_hucre22/10000,int_hucre22%10000);

		 if(arac_hizi <= 5)
		 		  		  {
		 		  hiz_ibresiderece = ((arac_hizi*3)+337);

		 		  }
		 		  if(arac_hizi > 5 && arac_hizi < 7)
		 						  		  {
		 						  hiz_ibresiderece = ((arac_hizi*5)+325);

		 						  }

		 		  if(arac_hizi >= 7 && arac_hizi < 10)
		 							  		  {
		 							  hiz_ibresiderece = (((arac_hizi*5)+326)-360);

		 							  }

		 		  if(arac_hizi >= 10)
		 							  		  {
		 							  hiz_ibresiderece = (arac_hizi*5)-37;

		 							  }

		 NEXTION_SendString(&H1, &h1s); //Hucre 1
		 NEXTION_SendString(&H2, &h2s); //Hucre 2
		 NEXTION_SendString(&H3, &h3s); //Hucre 3
		 NEXTION_SendString(&H4, &h4s); //Hucre 4
		 NEXTION_SendString(&H5, &h5s); //Hucre 5
		 NEXTION_SendString(&H6, &h6s); //Hucre 6
		 NEXTION_SendString(&H7,  &h7s); //Hucre 7
		 NEXTION_SendString(&H8,  &h8s); //Hucre 8
		 NEXTION_SendString(&H9,  &h9s); //Hucre 9
		 NEXTION_SendString(&H10, &h10s); //Hucre 10
		 NEXTION_SendString(&H11, &h11s); //Hucre 11
		 NEXTION_SendString(&H12, &h12s); //Hucre 12
		 NEXTION_SendString(&H13, &h13s); //Hucre 13
		 NEXTION_SendString(&H14, &h14s); //Hucre 14
		 NEXTION_SendString(&H15, &h15s); //Hucre 15
		 NEXTION_SendString(&H16, &h16s); //Hucre 16
		 NEXTION_SendString(&H17, &h17s); //Hucre 17
		 NEXTION_SendString(&H18, &h18s); //Hucre 18
		 NEXTION_SendString(&H19, &h19s); //Hucre 19
		 NEXTION_SendString(&H20, &h20s); //Hucre 20
		 NEXTION_SendString(&H21, &h21s); //Hucre 21
		 NEXTION_SendString(&H22, &h22s); //Hucre 22



		 NEXTION_SendString(&tsks, &kalansures); //Tam şarja kalan süre
		 NEXTION_SendString(&btg,  &topgerilims);  //Batarya toplam gerilim
		 NEXTION_SendString(&kem, &kalans);  //Kalan enerji miktarı
		 NEXTION_SendString(&sg,   &sarjgucus);  //sarj gücü

		 NEXTION_SendNum("z0",hiz_ibresiderece);
		 SendtoPB("j1.val",toplam_batarya); // Kalan batarya yüzdesi
		 SendtoPB("j0.val",batarya_sicaklik); // Batarya Sıcaklığı


		 		  NEXTION_SendNum("n0",arac_hizi); //dijital hız





		 sprintf(motors,"AF6%dB",motor_temp_tam);
		 LORA_SendString(&motors);
		 HAL_Delay(150);
		 sprintf(bataryas,"AF7%dB",bat_sicaklik);//batarya temp
		 LORA_SendString(&bataryas);
		 HAL_Delay(150);
		 sprintf(arachızs,"AF5%dB",arac_hiz);//arac hızı
		 LORA_SendString(&arachızs);
		 HAL_Delay(150);
		 sprintf(kalans,"AG1%dB",int_kalan_enerj_miktari/100);//kalan enerji miktarı
		 LORA_SendString(&kalans);
		 HAL_Delay(150);
		 sprintf(topgerilims,"AF9%dB",int_toplam_gerilim/100);//toplam gerilim
		 LORA_SendString(&topgerilims);
		 HAL_Delay(150);
		 sprintf(kalansures,"AG2%dB",kalan_sure);//kalan sure
		 LORA_SendString(&kalansures);
		 HAL_Delay(150);
		 sprintf(sarjgucus,"AG3%dB",sarj_gucu);//sarj gücü
		 LORA_SendString(&sarjgucus);
		 HAL_Delay(150);

		 //TOPLAMbatarya yüzdesi eksik AF8%dB
		 LORA_SendString("AF8100B");
		 HAL_Delay(150);


		 sprintf(h1s,"AD1%d.%dB",int_hucre1/10000,int_hucre1%10000);
		 LORA_SendString(&h1s);
		 HAL_Delay(15);
		 sprintf(h2s,"AD2%d.%dB",int_hucre2/10000,int_hucre2%10000);
		 LORA_SendString(&h2s);
		 HAL_Delay(150);
		 sprintf(h3s,"AD3%d.%dB",int_hucre3/10000,int_hucre3%10000);
		 LORA_SendString(&h3s);
		 HAL_Delay(150);
		 sprintf(h4s,"AD4%d.%dB",int_hucre4/10000,int_hucre4%10000);
		 LORA_SendString(&h4s);
		 HAL_Delay(150);
		 sprintf(h5s,"AD5%d.%dB",int_hucre5/10000,int_hucre5%10000);
		 LORA_SendString(&h5s);
		 HAL_Delay(150);
		 sprintf(h6s,"AD6%d.%dB",int_hucre6/10000,int_hucre6%10000);
		 LORA_SendString(&h6s);
		 HAL_Delay(150);
		 sprintf(h7s,"AD7%d.%dB",int_hucre7/10000,int_hucre7%10000);
		 LORA_SendString(&h7s);
		 HAL_Delay(150);
		 sprintf(h8s,"AD8%d.%dB",int_hucre8/10000,int_hucre8%10000);
		 LORA_SendString(&h8s);
		 HAL_Delay(150);
		 sprintf(h9s,"AD9%d.%dB",int_hucre9/10000,int_hucre9%10000);
		 LORA_SendString(&h9s);
		 HAL_Delay(150);
		 sprintf(h10s,"AE1%d.%dB",int_hucre10/10000,int_hucre10%10000);
		 LORA_SendString(&h10s);
		 HAL_Delay(150);
		 sprintf(h11s,"AE2%d.%dB",int_hucre11/10000,int_hucre11%10000);
		 LORA_SendString(&h11s);
		 HAL_Delay(150);
		 sprintf(h12s,"AE3%d.%dB",int_hucre12/10000,int_hucre12%10000);
		 LORA_SendString(h12s);
		 HAL_Delay(150);
		 sprintf(h13s,"AE4%d.%dB",int_hucre13/10000,int_hucre13%10000);
		 LORA_SendString(&h13s);
		 HAL_Delay(150);
		 sprintf(h14s,"AE5%d.%dB",int_hucre14/10000,int_hucre14%10000);
		 LORA_SendString(&h14s);
		 HAL_Delay(150);
		 sprintf(h15s,"AE6%d.%dB",int_hucre15/10000,int_hucre15%10000);
		 LORA_SendString(&h15s);
		 HAL_Delay(150);
		 sprintf(h16s,"AE7%d.%dB",int_hucre16/10000,int_hucre16%10000);
		 LORA_SendString(&h16s);
		 HAL_Delay(150);
		 sprintf(h17s,"AE8%d.%dB",int_hucre17/10000,int_hucre17%10000);
		 LORA_SendString(&h17s);
		 HAL_Delay(150);
		 sprintf(h18s,"AE9%d.%dB",int_hucre18/10000,int_hucre18%10000);
		 LORA_SendString(&h18s);
		 HAL_Delay(150);
		 sprintf(h19s,"AF1%d.%dB",int_hucre19/10000,int_hucre19%10000);
		 LORA_SendString(&h19s);
		 HAL_Delay(150);
		 sprintf(h20s,"AF2%d.%dB",int_hucre20/10000,int_hucre20%10000);
		 LORA_SendString(&h20s);
		 HAL_Delay(150);
		 sprintf(h21s,"AF3%d.%dB",int_hucre21/10000,int_hucre21%10000);
		 LORA_SendString(&h21s);
		 HAL_Delay(150);
		 sprintf(h22s,"AF4%d.%dB",int_hucre22/10000,int_hucre22%10000);
		 LORA_SendString(&h22s);
		 HAL_Delay(150);


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_112CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 21;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_10TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_5TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 8399;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 400-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 9600;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * @brief UART5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART5_Init(void)
{

  /* USER CODE BEGIN UART5_Init 0 */

  /* USER CODE END UART5_Init 0 */

  /* USER CODE BEGIN UART5_Init 1 */

  /* USER CODE END UART5_Init 1 */
  huart5.Instance = UART5;
  huart5.Init.BaudRate = 9600;
  huart5.Init.WordLength = UART_WORDLENGTH_8B;
  huart5.Init.StopBits = UART_STOPBITS_1;
  huart5.Init.Parity = UART_PARITY_NONE;
  huart5.Init.Mode = UART_MODE_TX_RX;
  huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart5.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart5) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART5_Init 2 */

  /* USER CODE END UART5_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */
  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9|GPIO_PIN_11|GPIO_PIN_13|GPIO_PIN_14, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PE9 PE11 PE13 PE14 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_11|GPIO_PIN_13|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
