/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoMergeSortComponent
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CEcoMergeSortComponent
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECOMERGESORTCOMPONENT_H__
#define __C_ECOMERGESORTCOMPONENT_H__

#include "IEcoMergeSortComponent.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoMergeSortComponent {

    /* Таблица функций интерфейса IEcoMergeSortComponent */
    IEcoMergeSortComponentVTbl* m_pVTblIEcoMergeSortComponent;


    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

    /* Данные экземпляра */
    char_t* m_Name;

} CEcoMergeSortComponent, *CEcoMergeSortComponentPtr;

/* Инициализация экземпляра */
int16_t initCEcoMergeSortComponent(/*in*/ struct IEcoMergeSortComponent* me, /* in */ IEcoUnknown *pIUnkSystem);
/* Создание экземпляра */
int16_t createCEcoMergeSortComponent(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoMergeSortComponent** ppIEcoMergeSortComponent);
/* Удаление */
void deleteCEcoMergeSortComponent(/* in */ IEcoMergeSortComponent* pIEcoMergeSortComponent);

#endif /* __C_ECOMERGESORTCOMPONENT_H__ */
