/**
 * \usergroup{SceAppUtil}
 * \usage{psp2/apputil.h,SceAppUtil_stub,SCE_SYSMODULE_APPUTIL}
 */


#ifndef _PSP2_APPUTL_H_
#define _PSP2_APPUTL_H_

#include <stdint.h>
#include <psp2/types.h>
#include <psp2/appmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SceAppUtilSaveDataRemoveMode {
	SCE_APPUTIL_SAVEDATA_DATA_REMOVE_MODE_DEFAULT = 0,
	SCE_APPUTIL_SAVEDATA_DATA_REMOVE_MODE_NO_SLOT = 1
} SceAppUtilSaveDataDataRemoveMode;

typedef enum SceAppUtilSaveDataSaveMode {
	SCE_APPUTIL_SAVEDATA_DATA_SAVE_MODE_FILE = 0,
	SCE_APPUTIL_SAVEDATA_DATA_SAVE_MODE_DIRECTORY = 2
} SceAppUtilSaveDataDataSaveMode;

typedef enum SceAppUtilErrorCode {
	SCE_APPUTIL_ERROR_PARAMETER                   = (int)0x80100600,
	SCE_APPUTIL_ERROR_NOT_INITIALIZED             = (int)0x80100601,
	SCE_APPUTIL_ERROR_NO_MEMORY                   = (int)0x80100602,
	SCE_APPUTIL_ERROR_BUSY                        = (int)0x80100603,
	SCE_APPUTIL_ERROR_NOT_MOUNTED                 = (int)0x80100604,
	SCE_APPUTIL_ERROR_NO_PERMISSION               = (int)0x80100605,
	SCE_APPUTIL_ERROR_PASSCODE_MISMATCH           = (int)0x80100606,
	SCE_APPUTIL_ERROR_APPEVENT_PARSE_INVALID_DATA = (int)0x80100620,
	SCE_APPUTIL_ERROR_SAVEDATA_SLOT_EXISTS        = (int)0x80100640,
	SCE_APPUTIL_ERROR_SAVEDATA_SLOT_NOT_FOUND     = (int)0x80100641,
	SCE_APPUTIL_ERROR_SAVEDATA_NO_SPACE_QUOTA     = (int)0x80100642,
	SCE_APPUTIL_ERROR_SAVEDATA_NO_SPACE_FS        = (int)0x80100643,
	SCE_APPUTIL_ERROR_DRM_NO_ENTITLEMENT          = (int)0x80100660,
	SCE_APPUTIL_ERROR_PHOTO_DEVICE_NOT_FOUND      = (int)0x80100680,
	SCE_APPUTIL_ERROR_MUSIC_DEVICE_NOT_FOUND      = (int)0x80100685,
	SCE_APPUTIL_ERROR_MOUNT_LIMIT_OVER            = (int)0x80100686,
	SCE_APPUTIL_ERROR_STACKSIZE_TOO_SHORT         = (int)0x801006A0
} SceAppUtilErrorCode;

typedef unsigned int SceAppUtilBootAttribute;
typedef unsigned int SceAppUtilAppEventType;
typedef unsigned int SceAppUtilSaveDataSlotId;
typedef SceAppMgrSaveDataSlotStatus SceAppUtilSaveDataSlotStatus;
typedef unsigned int SceAppUtilAppParamId;
typedef unsigned int SceAppUtilBgdlStatusType;

typedef struct SceAppUtilBgdlStatus {
	SceAppUtilBgdlStatusType type;
	SceUInt32 addcontNumReady;
	SceUInt32 addcontNumNotReady;
	SceUInt32 licenseReady;
	SceChar8 reserved[28];
} SceAppUtilBgdlStatus;

typedef struct SceAppUtilInitParam {
	SceSize workBufSize;  //!< Buffer size
	uint8_t reserved[60]; //!< Reserved range
} SceAppUtilInitParam;

typedef struct SceAppUtilBootParam {
	SceAppUtilBootAttribute attr;   //!< Boot attribute
	unsigned int appVersion;        //!< App version
	uint8_t reserved[32];           //!< Reserved range
} SceAppUtilBootParam;

typedef struct SceAppUtilAppEventParam {
	SceAppUtilAppEventType type; //!< Event type
	uint8_t dat[1024];           //!< Event parameter
} SceAppUtilAppEventParam;

typedef SceAppMgrMountPoint SceAppUtilMountPoint;

typedef struct SceAppUtilSaveDataSlotEmptyParam {
	SceWChar16 *title;     //!< Title string
	char *iconPath;        //!< Path to icon
	void *iconBuf;         //!< Icon buffer
	SceSize iconBufSize;   //!< Icon buffer size
	uint8_t reserved[32];  //!< Reserved range
} SceAppUtilSaveDataSlotEmptyParam;

typedef struct SceAppUtilSaveDataSlot {
	SceAppUtilSaveDataSlotId id;                  //!< Slot id
	SceAppUtilSaveDataSlotStatus status;          //!< Slot status
	int userParam;                                //!< Param for free usage
	SceAppUtilSaveDataSlotEmptyParam *emptyParam; //!< Settings for empty slot
} SceAppUtilSaveDataSlot;

typedef SceAppMgrSaveDataSlotParam SceAppUtilSaveDataSlotParam;

typedef struct SceAppUtilSaveDataSaveItem {
	const char *dataPath;             //!< Path to savedata
	const void *buf;                  //!< Buffer of savedata file
	uint32_t pad;                     //!< Padding
	SceOff offset;                    //!< Offset of savedata file
	int mode;                         //!< Savedata save mode (One of ::SceAppUtilSaveDataSaveMode)
	uint8_t reserved[36];             //!< Reserved range
} SceAppUtilSaveDataSaveItem;

typedef SceAppMgrSaveDataDataSaveItem SceAppUtilSaveDataDataSaveItem;

typedef struct SceAppUtilSaveDataFileSlot {
	unsigned int id;
	SceAppUtilSaveDataSlotParam *slotParam;
	uint8_t reserved[32];
} SceAppUtilSaveDataFileSlot;

typedef struct SceAppUtilSaveDataRemoveItem {
	const char *dataPath;               //!< Path to savedata data
	int mode;                           //!< Savedata remove mode (One of ::SceAppUtilSaveDataRemoveMode)
	uint8_t reserved[36];               //!< Reserved range
} SceAppUtilSaveDataRemoveItem;

typedef struct SceAppUtilStoreBrowseParam {
	unsigned int type;          //!< Store browse type
	const char *id;             //!< Target id
} SceAppUtilStoreBrowseParam;

typedef struct SceAppUtilWebBrowserParam {
	const char *str;            //!< String that's passed to command specified by launchMode
	SceSize strlen;	            //!< Length of str
	unsigned int launchMode;    //!< Browser mode
	unsigned int reserved;      //!< Reserved area
} SceAppUtilWebBrowserParam;

/**
 * Initializes the AppUtil library. Call this before any of the other functions.
 *
 * @param[out] initParam - App init info. Must be initialized with zeros.
 * @param[out] bootParam - App boot info. Must be initialized with zeros.
 *
 * @return 0 on success, < 0 on error.
 */
int sceAppUtilInit(SceAppUtilInitParam *initParam, SceAppUtilBootParam *bootParam);

//! Shutdown AppUtil library
int sceAppUtilShutdown();

//! Receive app event
int sceAppUtilReceiveAppEvent(SceAppUtilAppEventParam *eventParam);

//! Parse received app event from LiveArea
int sceAppUtilAppEventParseLiveArea(const SceAppUtilAppEventParam *eventParam, char *buffer);

//! Create savedata slot
int sceAppUtilSaveDataSlotCreate(unsigned int slotId,
	SceAppUtilSaveDataSlotParam *param,
	SceAppUtilMountPoint *mountPoint);

//! Delete savedata slot
int sceAppUtilSaveDataSlotDelete(unsigned int slotId,
	SceAppUtilMountPoint *mountPoint);

//! Set savedata slot param
int sceAppUtilSaveDataSlotSetParam(unsigned int slotId,
	SceAppUtilSaveDataSlotParam *param,
	SceAppUtilMountPoint *mountPoint);

//! Get savedata slot param
int sceAppUtilSaveDataSlotGetParam(unsigned int slotId,
	SceAppUtilSaveDataSlotParam *param,
	SceAppUtilMountPoint *mountPoint);

//!< Write savedata files and directories
int sceAppUtilSaveDataDataSave(SceAppUtilSaveDataFileSlot *slot,
	SceAppUtilSaveDataDataSaveItem *files, unsigned int fileNum,
	SceAppUtilMountPoint *mountPoint,
	SceSize *requiredSizeKB);

//!< Delete savedata files
int sceAppUtilSaveDataDataRemove(SceAppUtilSaveDataFileSlot *slot,
	SceAppUtilSaveDataRemoveItem *files, unsigned int fileNum,
	SceAppUtilMountPoint *mountPoint);

//! Mount music data
int sceAppUtilMusicMount();

//! Unmount music data
int sceAppUtilMusicUmount();

//! Mount photo data
int sceAppUtilPhotoMount();

//! Unmount photo data
int sceAppUtilPhotoUmount();

//! Get system parameters for int type
int sceAppUtilSystemParamGetInt(unsigned int paramId, int *value);

//! Get application parameters for string type
int sceAppUtilSystemParamGetString(unsigned int paramId,
	SceChar8 *buf, SceSize bufSize);

//! Get application parameters for int type
int sceAppUtilAppParamGetInt(SceAppUtilAppParamId paramId, int *value);

//! Save safe memory
int sceAppUtilSaveSafeMemory(void *buf, SceSize bufSize, SceOff offset);

//! Load safe memory
int sceAppUtilLoadSafeMemory(void *buf, SceSize bufSize, SceOff offset);

//! Launch PSN Store
int sceAppUtilStoreBrowse(SceAppUtilStoreBrowseParam *param);

//! Get background download status
int sceAppUtilBgdlGetStatus(SceAppUtilBgdlStatus *stat);

//! Launch web browser app
int sceAppUtilLaunchWebBrowser(SceAppUtilWebBrowserParam *param);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_APPUTL_H_ */

