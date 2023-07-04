#include "LedControl.h"

LedControl lc = LedControl(12, 11, 10, 4); //Din, ClK, CS

byte data[10][8] =
{
  // 미
  {
    B00000001, 
    B01111101, 
    B01000101, 
    B01000101, 
    B01000101, 
    B01111101, 
    B00000001, 
    B00000000
  },
  // 끄
  {
    B00111110,
    B00010010,
    B00010010,
    B00010010,
    B00000000,
    B01111111,
    B00000000,
    B00000000
  },
  // 럼
  {
   B01110010,
   B00010010,
   B01110110,
   B01000010,
   B01110010,
   B00001110,
   B00001010,
   B00001110
  },
  // NULL
  {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  // 주
  {
    B00111110,
    B00000100,
    B00001000,
    B00010100,
    B00100010,
    B00000000,
    B01111111,
    B00001000
  },
  // 의
  {
    B00010010,
    B00101010,
    B00101010,
    B00010010,
    B00000010,
    B01111110,
    B00000010,
    B00000000
  },
  // NULL
  {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  // NULL
  {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  },
  // NULL
  {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
  }
};

void setup()
{
  for (int num = 0; num < 4; num++)
  {
    lc.shutdown(num, false); //절전모드 해제
    lc.setIntensity(num, 8); //매트릭스의 밝기 8로 선언, 0~15까지 가능
    lc.clearDisplay(num); //매트릭스 led 초기화
  }
}


void loop()
{
  byte buffer1[4 + 1][8];

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      buffer1[i][j] = B00000000;
    }
  }

  // 문자 시프트 작업
  for (int i = 0; i < 10; i++) // 전체 글자수 만큼 반복
  {
    // memcpy 함수를 사용해서 데이터를 버퍼로 옮김
    // memcpy(destination, source, size)
    // memcpy(목적지 주소값, 원본 주소값, 데이터크기)
    memcpy(&buffer1[4], &data[i], sizeof(data[i]));

    for (int j = 0; j < 8; j++) // 한 글자는 8열이므로, 글자당 8번 수행
    {
      for (int k = 0; k < 8; k++) // 한 글자는 8행이므로, 글자당 8번 수행
      {
        // 비트 시프트로 왼쪽으로 한칸씩 시프트
        // 비트 시프트로 첫번째 열의 데이터가 오른쪽으로 7칸 시프트
        // 비트 OR 연산자(|)로 두 데이터를 합침
        buffer1[0][k] = (buffer1[0][k] << 1) | (buffer1[1][k] >> 7);
        buffer1[1][k] = (buffer1[1][k] << 1) | (buffer1[2][k] >> 7);
        buffer1[2][k] = (buffer1[2][k] << 1) | (buffer1[3][k] >> 7);
        buffer1[3][k] = (buffer1[3][k] << 1) | (buffer1[4][k] >> 7);
        buffer1[4][k] = (buffer1[4][k] << 1);
      }

      // 출력
      /*for (int i = 0; i < 8; i++)
      {
        // lc.setRow 함수는 행(Row) 기준으로 도트매트릭스를 제어
        // lc.setRow(matrix_number,Row,value)
        // lc.setRow(출력 매트릭스 번호, 행, 출력값)
        lc.setRow(0, i, buffer1[0][i]);
        lc.setRow(1, i, buffer1[1][i]);
        lc.setRow(2, i, buffer1[2][i]);
        lc.setRow(3, i, buffer1[3][i]);
      }*/
      //뒤집혀서 출력 될 시
      for (int i = 0; i < 8; i++)
      {
        // lc.setRow 함수는 행(Row) 기준으로 도트매트릭스를 제어
        // lc.setRow(matrix_number,Row,value)
        // lc.setRow(출력 매트릭스 번호, 행, 출력값)
        lc.setRow(0, i, buffer1[3][i]);
        lc.setRow(1, i, buffer1[2][i]);
        lc.setRow(2, i, buffer1[1][i]);
        lc.setRow(3, i, buffer1[0][i]);
      }
      delay(10);
    }
  }
  delay(1000);
}
