#include <cmath>
#include <cstdio>
#include <cstring>
#include <windows.h>

// --- Terminal groesse ---
const int width = 120;
const int height = 40;

char buffer[width * height];
float zBuffer[width * height];

const int backgroundASCIICode = ' ';
const float K1 = 55;
const int distanceFromCam = 100;
const float cubeSize = 20;

float A = 0.0f, B = 0.0f;

// ANSI-Unterstuetzung fuer Windows aktivieren
static void enableANSI()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

// Konsolenfenster auf gewuenschte Groesse setzen
static void setConsoleSize(int cols, int rows)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // Erst Puffer, dann Fenster (Reihenfolge wichtig)
    COORD bufSize = {(SHORT)cols, (SHORT)(rows + 1)};
    SetConsoleScreenBufferSize(hOut, bufSize);

    SMALL_RECT winRect = {0, 0, (SHORT)(cols - 1), (SHORT)(rows - 1)};
    SetConsoleWindowInfo(hOut, TRUE, &winRect);
}

// Cursor ausblenden (verhindert Flicker)
static void hideCursor()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ci;
    GetConsoleCursorInfo(hOut, &ci);
    ci.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &ci);
}

void rotateX(float &y, float &z, float angle)
{
    float newY = y * cos(angle) - z * sin(angle);
    float newZ = y * sin(angle) + z * cos(angle);
    y = newY;
    z = newZ;
}

void rotateY(float &x, float &z, float angle)
{
    float newX = x * cos(angle) + z * sin(angle);
    float newZ = -x * sin(angle) + z * cos(angle);
    x = newX;
    z = newZ;
}

void projectPoint(float x, float y, float z, int &xp, int &yp, float &ooz)
{
    ooz = 1.0f / (z + distanceFromCam);
    xp = (int)(width / 2 + K1 * ooz * x * 2);
    yp = (int)(height / 2 - K1 * ooz * y);
}

void renderLine(float x1, float y1, float z1,
                float x2, float y2, float z2, char ch)
{
    rotateX(y1, z1, A);
    rotateY(x1, z1, B);
    rotateX(y2, z2, A);
    rotateY(x2, z2, B);

    int xp1, yp1, xp2, yp2;
    float ooz1, ooz2;
    projectPoint(x1, y1, z1, xp1, yp1, ooz1);
    projectPoint(x2, y2, z2, xp2, yp2, ooz2);

    int dx = abs(xp2 - xp1), sx = xp1 < xp2 ? 1 : -1;
    int dy = -abs(yp2 - yp1), sy = yp1 < yp2 ? 1 : -1;
    int err = dx + dy, e2;

    while (true)
    {
        int idx = xp1 + yp1 * width;
        if (xp1 >= 0 && xp1 < width && yp1 >= 0 && yp1 < height)
        {
            if (ooz1 > zBuffer[idx])
            {
                zBuffer[idx] = ooz1;
                buffer[idx] = ch;
            }
        }
        if (xp1 == xp2 && yp1 == yp2)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            xp1 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            yp1 += sy;
        }
    }
}

int main()
{
    enableANSI();
    setConsoleSize(width, height);
    hideCursor();

    // Bildschirm einmal leeren
    printf("\x1b[2J");

    while (true)
    {
        memset(buffer, backgroundASCIICode, width * height);
        memset(zBuffer, 0, width * height * sizeof(float));

        A += 0.02f;
        B += 0.015f;

        float cube[8][3] = {
            {-cubeSize, -cubeSize, -cubeSize},
            {cubeSize, -cubeSize, -cubeSize},
            {cubeSize, cubeSize, -cubeSize},
            {-cubeSize, cubeSize, -cubeSize},
            {-cubeSize, -cubeSize, cubeSize},
            {cubeSize, -cubeSize, cubeSize},
            {cubeSize, cubeSize, cubeSize},
            {-cubeSize, cubeSize, cubeSize},
        };

        renderLine(cube[0][0], cube[0][1], cube[0][2], cube[1][0], cube[1][1], cube[1][2], '#');
        renderLine(cube[1][0], cube[1][1], cube[1][2], cube[2][0], cube[2][1], cube[2][2], '#');
        renderLine(cube[2][0], cube[2][1], cube[2][2], cube[3][0], cube[3][1], cube[3][2], '#');
        renderLine(cube[3][0], cube[3][1], cube[3][2], cube[0][0], cube[0][1], cube[0][2], '#');
        renderLine(cube[4][0], cube[4][1], cube[4][2], cube[5][0], cube[5][1], cube[5][2], '#');
        renderLine(cube[5][0], cube[5][1], cube[5][2], cube[6][0], cube[6][1], cube[6][2], '#');
        renderLine(cube[6][0], cube[6][1], cube[6][2], cube[7][0], cube[7][1], cube[7][2], '#');
        renderLine(cube[7][0], cube[7][1], cube[7][2], cube[4][0], cube[4][1], cube[4][2], '#');
        renderLine(cube[0][0], cube[0][1], cube[0][2], cube[4][0], cube[4][1], cube[4][2], '#');
        renderLine(cube[1][0], cube[1][1], cube[1][2], cube[5][0], cube[5][1], cube[5][2], '#');
        renderLine(cube[2][0], cube[2][1], cube[2][2], cube[6][0], cube[6][1], cube[6][2], '#');
        renderLine(cube[3][0], cube[3][1], cube[3][2], cube[7][0], cube[7][1], cube[7][2], '#');

        // Cursor zurueck nach oben, ganzen Frame auf einmal ausgeben
        static char frame[width * height + height + 10];
        int pos = 0;
        frame[pos++] = '\x1b';
        frame[pos++] = '[';
        frame[pos++] = 'H';
        for (int i = 0; i < width * height; i++)
        {
            frame[pos++] = buffer[i];
            if (i % width == width - 1)
                frame[pos++] = '\n';
        }
        fwrite(frame, 1, pos, stdout);
        fflush(stdout);

        // Frame-Rate: ~60fps
        Sleep(16);
    }

    return 0;
}