/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoMergeSortComponent
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoMergeSortComponent
 * </описание>
 *
 * <ссылка>
 *
 * </ссылка>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECOMERGESORTCOMPONENT_H__
#define __I_ECOMERGESORTCOMPONENT_H__

#include "IEcoBase1.h"

/* IEcoMergeSortComponent IID = {A301546D-6977-4B58-8F18-CFD8536718ED} */
#ifndef __IID_IEcoMergeSortComponent
static const UGUID IID_IEcoMergeSortComponent = {0x01, 0x10, 0xA3, 0x01, 0x54, 0x6D, 0x69, 0x77, 0x4B, 0x58, 0x8F, 0x18, 0xCF, 0xD8, 0x53, 0x67, 0x18, 0xED};
#endif /* __IID_IEcoMergeSortComponent */

typedef struct IEcoMergeSortComponentVTbl {

    /* IEcoUnknown */
    int16_t (*QueryInterface)(/* in */ struct IEcoMergeSortComponent* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (*AddRef)(/* in */ struct IEcoMergeSortComponent* me);
    uint32_t (*Release)(/* in */ struct IEcoMergeSortComponent* me);

    /* IEcoMergeSortComponent */
    int16_t (*CEcoMergeSortComponent_Qsort)(/* in */ struct IEcoMergeSortComponent* me, /* in */ void* first, /* in */ int32_t number, /* in */ int32_t size, int16_t (*comparator) (const void *, const void *));

} IEcoMergeSortComponentVTbl, *IEcoMergeSortComponentVTblPtr;

interface IEcoMergeSortComponent {
    struct IEcoMergeSortComponentVTbl *pVTbl;
} IEcoMergeSortComponent;


#endif /* __I_ECOMERGESORTCOMPONENT_H__ */
