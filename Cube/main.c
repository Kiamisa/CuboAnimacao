#include <math.h>
#include <stdio.h>
#include <string.h>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
void usleep(__int64 usec) {
    HANDLE timer;
    LARGE_INTEGER ft;
    ft.QuadPart = -(10 * usec);
    timer = CreateWaitableTimer(NULL, TRUE, NULL);
    SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
    WaitForSingleObject(timer, INFINITE);
    CloseHandle(timer);
}
#endif

#define LARGURA 160
#define ALTURA 44
#define PLANO_FUNDO_ASCII '.'
#define DISTANCIA_CAM 100
#define K1 40
#define VELOCIDADE_INCREMENTO 0.6

float A, B, C; // Representação de rotação nos eixos X, Y, Z
float larguraCubo = 20;
float zBuffer[LARGURA * ALTURA];
char buffer[LARGURA * ALTURA];
float OffsetHorizontal;

float calculoX(int i, int j, int k) {
    return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) + j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

float calculoY(int i, int j, int k) {
    return j * cos(A) * cos(C) + k * sin(A) * cos(C) - j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) - i * cos(B) * sin(C);
}

float calculoZ(int i, int j, int k) {
    return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

void calculoSuperficie(float cuboX, float cuboY, float cuboZ, int ch) {
    float x = calculoX(cuboX, cuboY, cuboZ);
    float y = calculoY(cuboX, cuboY, cuboZ);
    float z = calculoZ(cuboX, cuboY, cuboZ) + DISTANCIA_CAM;
    float ooz = 1 / z;

    int xp = (int)(LARGURA / 2 + OffsetHorizontal + K1 * ooz * x * 2);
    int yp = (int)(ALTURA / 2 + K1 * ooz * y);
    int idx = xp + yp * LARGURA;

    if (idx >= 0 && idx < LARGURA * ALTURA) {
        if (ooz > zBuffer[idx]) {
            zBuffer[idx] = ooz;
            buffer[idx] = ch;
        }
    }
}

void desenharCubo(float larguraCubo, float offsetHorizontal, char ch1, char ch2, char ch3, char ch4, char ch5, char ch6) {
    OffsetHorizontal = offsetHorizontal;
    for (float cuboX = -larguraCubo; cuboX < larguraCubo; cuboX += VELOCIDADE_INCREMENTO) {
        for (float cuboY = -larguraCubo; cuboY < larguraCubo; cuboY += VELOCIDADE_INCREMENTO) {
            calculoSuperficie(cuboX, cuboY, -larguraCubo, ch1);
            calculoSuperficie(larguraCubo, cuboY, cuboX, ch2);
            calculoSuperficie(-larguraCubo, cuboY, cuboX, ch3);
            calculoSuperficie(-cuboX, cuboY, larguraCubo, ch4);
            calculoSuperficie(cuboX, -larguraCubo, -cuboY, ch5);
            calculoSuperficie(cuboX, larguraCubo, cuboY, ch6);
        }
    }
}

int main() {
    printf("\x1b[2J");

    while (1) {
        memset(buffer, PLANO_FUNDO_ASCII, LARGURA * ALTURA);
        memset(zBuffer, 0, sizeof(zBuffer));

        // Desenhar cubos
        desenharCubo(20, -2 * 20, '$', '@', '#', '~', '+', ';');
        // desenharCubo(10, 1 * 10, '$', '@', '#', '~', '+', ';');
        // desenharCubo(5, 8 * 5, '$', '@', '#', '~', '+', ';');

        printf("\x1b[H");
        for (int k = 0; k < LARGURA * ALTURA; k++) {
            putchar(k % LARGURA ? buffer[k] : 10);
        }

        A += 0.05;
        B += 0.05;
        C += 0.01;

        usleep(8000 * 2);
    }
    return 0;
}
