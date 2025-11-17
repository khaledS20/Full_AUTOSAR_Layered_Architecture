/******************************************************************************
 * File Name: Det.h
 *
 * Module: Dio
 *
 * File Description: Det stores the development errors reported by other modules.
 *                   This source file is a STUB for the Det Module
 *
 * Author: Khaled Saleh
 ******************************************************************************/

#ifndef DET_H_
#define DET_H_

#define DET_VENDOR_ID           (1111U)

#define MODULE_ID               (15U)

#define DET_INSTANCE_ID         (0U)

/*
 * AUTOSAR version 4.0.3
 */
#define DET_AR_MAJOR_VERSION    (4U)
#define DET_AR_MINOR_VERSION    (0U)
#define DET_AR_PATCH_VERSION    (3U)

/*
 * Software release version 1.0.0
 */
#define DET_SW_MAJOR_VERSION    (1U)
#define DET_SW_MINOR_VERSION    (0U)
#define DET_SW_PATCH_VERSION    (OU)

/* Standard AUTOSAR types */
#include "Std_Types.h"
/*
 * AUTOSAR version checking for the DET module and the standard types file
 */
#if ((DET_AR_MAJOR_VERSION != STD_TYPES_AR_RELEASE_MAJOR_VERSION)\
 ||  (DET_AR_MINOR_VERSION != STD_TYPES_AR_RELEASE_MINOR_VERSION)\
 ||  (DET_AR_PATCH_VERSION != STD_TYPES_AR_RELEASE_PATCH_VERSION))

 #error "The AR version of the DET module and STD types doesn't match"
#endif


/*********************************************************************************
 *                              External Variables                               *
 *********************************************************************************/
extern uint16 Det_ModuleId ;
extern uint8 Det_InstanceId ;
extern uint8 Det_ApiId ;
extern uint8 Det_ErrorId ;

/*********************************************************************************
 *                              Function Prototypes                              *
 *********************************************************************************/
Std_ReturnType Det_ReportError
(
        uint16 ModuleId,
        uint8 InstanceId,
        uint8 ApiId,
        uint8 ErrorId
);

#endif /* DET_H_ */



