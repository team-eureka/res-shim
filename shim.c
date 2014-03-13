#include <stdlib.h>

typedef struct {
	int a;
	int b;
} MV_PE_Handle;

int MV_OSAL_Init (void);
int MV_OSAL_Exit (void);
int MV_OSAL_Task_Sleep (int delay);

int MV_PE_Init (MV_PE_Handle **h);
int MV_PE_Remove (MV_PE_Handle *h);
int MV_PE_VOutSetEnable (MV_PE_Handle *h, int cpcb_id, int enabled);
int MV_PE_VOutSetCPCBResolutionBDEx (MV_PE_Handle *h, int cpcb_id, unsigned char res_id, unsigned char bit_depth, int a);
int MV_PE_VOutHDMISetVideoFormat (MV_PE_Handle *h, int a, int b, int c, int d);
int MV_PE_VOutHDMISetAudioFormat (MV_PE_Handle *h, int a, int b, int c, int d);
int MV_PE_VOutSetVisible (MV_PE_Handle *h, int a, int b);
int MV_PE_VOutHDMIGetSinkCaps (MV_PE_Handle *h, int a, void *caps);

int main (void) {
	MV_PE_Handle *h;

	MV_OSAL_Init();
	MV_PE_Init(&h);

	void *caps = calloc(1, 1508);
	MV_PE_VOutHDMIGetSinkCaps(h, 1, caps);
	free(caps);

	MV_PE_VOutSetEnable(h, 0, 0);
	MV_OSAL_Task_Sleep(100);

	MV_PE_VOutSetCPCBResolutionBDEx(h, 0, 15, 2, 0);
	MV_PE_VOutHDMISetVideoFormat(h, 1, 1, 2, 1);
	MV_PE_VOutHDMISetAudioFormat(h, 1, 15, 1, 0);

	MV_PE_VOutSetEnable(h, 0, 1);
	MV_OSAL_Task_Sleep(100);

	MV_PE_VideoSetVisible(h, 3, 1);

	MV_PE_Remove(h);
	MV_OSAL_Exit();

	return EXIT_SUCCESS;
}
