/*
 * Вращающийся ASCII-пончик (тор) в консоли.
 * Реализовано БЕЗ единого массива — только циклы, условия и printf.
 *
 * Компиляция (Linux/macOS):
 *   gcc donut.c -o donut -lm
 *   ./donut
 *
 * Компиляция (Windows, MinGW):
 *   gcc donut.c -o donut.exe -lm
 *   donut.exe
 *   (если usleep не найдётся — см. блок #ifdef _WIN32 ниже, он уже обработан)
 *
 * Остановить программу: Ctrl+C
 */

#include <stdio.h>
#include <math.h>

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP_MS(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

int main(void) {
    /* Углы поворота тора вокруг осей X (A) и Z (B) — меняются со временем */
    float A = 0.0f, B = 0.0f;

    /* Геометрия тора */
    const float R1 = 1.0f;   /* радиус трубки (сечения) */
    const float R2 = 2.0f;   /* радиус самого кольца */
    const float K2 = 5.0f;   /* расстояние от зрителя до тора */

    /* Размер "экрана" в символах */
    const int screenW = 80;
    const int screenH = 22;

    /* Масштаб проекции, чтобы фигура вписалась в экран */
    const float K1 = screenW * K2 * 3.0f / (8.0f * (R1 + R2));

    while (1) {
        /* Очистка экрана и перевод курсора в левый верхний угол */
        printf("\x1b[2J\x1b[H");

        float cosA = cosf(A), sinA = sinf(A);
        float cosB = cosf(B), sinB = sinf(B);

        /* Обходим всю поверхность тора двумя углами: theta (сечение) и phi (вокруг кольца) */
        for (float theta = 0.0f; theta < 6.2832f; theta += 0.07f) {

            float costheta = cosf(theta);
            float sintheta = sinf(theta);

            for (float phi = 0.0f; phi < 6.2832f; phi += 0.02f) {

                float cosphi = cosf(phi);
                float sinphi = sinf(phi);

                /* Точка на окружности сечения тора */
                float circlex = R2 + R1 * costheta;
                float circley = R1 * sintheta;

                /* Поворачиваем точку вокруг тора (phi) и сам тор в пространстве (A, B) */
                float x = circlex * (cosB * cosphi + sinA * sinB * sinphi) - circley * cosA * sinB;
                float y = circlex * (sinB * cosphi - sinA * cosB * sinphi) + circley * cosA * cosB;
                float z = K2 + cosA * circlex * sinphi + circley * sinA;
                float ooz = 1.0f / z; /* "1 / глубина" — чем больше, тем ближе точка к зрителю */

                /* Проекция 3D -> 2D (перспектива) */
                int xp = (int)(screenW / 2 + K1 * ooz * x);
                int yp = (int)(screenH / 2 - K1 * ooz * y * 0.5f); /* *0.5 компенсирует высоту символа */

                /* "Яркость" точки — насколько она обращена к источнику света.
                   Если <= 0, точка смотрит от зрителя — не рисуем её (это и убирает
                   необходимость в honбuffer/z-buffer массиве). */
                float luminance = cosphi * costheta * sinB
                                 - cosA * costheta * sinphi
                                 - sinA * sintheta
                                 + cosB * (cosA * sintheta - costheta * sinA * sinphi);

                if (luminance > 0 && xp >= 0 && xp < screenW && yp >= 0 && yp < screenH) {

                    int idx = (int)(luminance * 8.0f);

                    /* Выбираем символ по яркости без массива — просто цепочка условий */
                    char c;
                    if (idx <= 0)      c = '.';
                    else if (idx == 1) c = ',';
                    else if (idx == 2) c = '-';
                    else if (idx == 3) c = '~';
                    else if (idx == 4) c = ':';
                    else if (idx == 5) c = ';';
                    else if (idx == 6) c = '=';
                    else if (idx == 7) c = '!';
                    else if (idx == 8) c = '*';
                    else if (idx == 9) c = '#';
                    else if (idx == 10) c = '$';
                    else               c = '@';

                    /* Перемещаем курсор в нужную позицию и печатаем символ */
                    printf("\x1b[%d;%dH%c", yp + 1, xp + 1, c);
                }
            }
        }

        fflush(stdout);

        /* Крутим тор дальше */
        A += 0.07f;
        B += 0.03f;

        SLEEP_MS(30);
    }

    return 0;
}
