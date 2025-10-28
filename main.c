#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>

PSP_MODULE_INFO("PSPong by @aesnn", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);

int exit_callback(int arg1, int arg2, void *common)
{
    sceKernelExitGame();
    return 0;
}

int callback_thread(SceSize args, void *argp)
{
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();
    return 0;
}

int setup_callbacks(void)
{
    int thid = sceKernelCreateThread("update_thread", callback_thread, 0x11, 0xFA0, 0, 0);
    if (thid >= 0)
        sceKernelStartThread(thid, 0, 0);
    return thid;
}

int main(void)
{
    setup_callbacks();
    pspDebugScreenInit();
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    SceCtrlData pad;

    const int screenW = 60;
    const int screenH = 33;

    int paddleY = screenH / 2;
    const int paddleX = 2;
    const int paddleSize = 4;

    float ballX = screenW / 2;
    float ballY = screenH / 2;
    float velX = 0.5f;
    float velY = 0.3f;

    pspDebugScreenSetXY(0, 0);
    pspDebugScreenClear();
    pspDebugScreenPrintf("\n\n\n\n\n");
    pspDebugScreenPrintf("         PSPong\n");
    pspDebugScreenPrintf("         by @aesnn on GitHub\n\n");
    pspDebugScreenPrintf("         Press X to start the game\n");

    while (1)
    {
        sceCtrlReadBufferPositive(&pad, 1);
        if (pad.Buttons & PSP_CTRL_CROSS)
            break;
        sceDisplayWaitVblankStart();
    }

    while (1)
    {
        sceCtrlReadBufferPositive(&pad, 1);

        if (pad.Buttons & PSP_CTRL_UP && paddleY > 0)
            paddleY--;
        if (pad.Buttons & PSP_CTRL_DOWN && paddleY < screenH - paddleSize)
            paddleY++;

        ballX += velX;
        ballY += velY;

        if (ballY < 0 || ballY > screenH - 1)
            velY = -velY;

        if ((int)ballX == paddleX + 1 && (int)ballY >= paddleY && (int)ballY <= paddleY + paddleSize)
            velX = -velX;

        if (ballX >= screenW - 1)
            velX = -velX;

        if (ballX < 0)
        {
            pspDebugScreenSetXY(0, 0);
            pspDebugScreenPrintf("Game Over!\nPress X to restart.\n");
            while (1)
            {
                sceCtrlReadBufferPositive(&pad, 1);
                if (pad.Buttons & PSP_CTRL_CROSS)
                {
                    ballX = screenW / 2;
                    ballY = screenH / 2;
                    velX = 0.5f;
                    velY = 0.3f;
                    paddleY = screenH / 2;
                    break;
                }
                sceDisplayWaitVblankStart();
            }
        }

        pspDebugScreenSetXY(0, 0);
        pspDebugScreenClear();

        for (int i = 0; i < paddleSize; i++)
        {
            pspDebugScreenSetXY(paddleX, paddleY + i);
            pspDebugScreenPrintf("|");
        }

        pspDebugScreenSetXY((int)ballX, (int)ballY);
        pspDebugScreenPrintf("O");

        pspDebugScreenSetXY(screenW - 14, screenH - 1);
        pspDebugScreenPrintf("@aesnn");

        sceDisplayWaitVblankStart();
    }

    return 0;
}
