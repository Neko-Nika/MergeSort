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
 *   Данный исходный код описывает реализацию интерфейсов CEcoMergeSortComponent
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoMergeSortComponent.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoMergeSortComponent
 * </описание>
 *
 */
int16_t CEcoMergeSortComponent_QueryInterface(/* in */ struct IEcoMergeSortComponent* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoMergeSortComponent* pCMe = (CEcoMergeSortComponent*)me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoMergeSortComponent) ) {
        *ppv = &pCMe->m_pVTblIEcoMergeSortComponent;
        pCMe->m_pVTblIEcoMergeSortComponent->AddRef((IEcoMergeSortComponent*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoMergeSortComponent;
        pCMe->m_pVTblIEcoMergeSortComponent->AddRef((IEcoMergeSortComponent*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoMergeSortComponent
 * </описание>
 *
 */
uint32_t CEcoMergeSortComponent_AddRef(/* in */ struct IEcoMergeSortComponent* me) {
    CEcoMergeSortComponent* pCMe = (CEcoMergeSortComponent*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoMergeSortComponent
 * </описание>
 *
 */
uint32_t CEcoMergeSortComponent_Release(/* in */ struct IEcoMergeSortComponent* me) {
    CEcoMergeSortComponent* pCMe = (CEcoMergeSortComponent*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoMergeSortComponent((IEcoMergeSortComponent*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
/*
 *
 * <сводка>
 *   Функция merge
 * </сводка>
 *
 * <описание>
 *   Рекурсивная функция слияния
 * </описание>
 *
 */

void merge(/* in */ IEcoMemoryAllocator1* pIMem, /* in */ void* first, /* in */ int32_t size, /* in */ int16_t (*cmp) (const void *, const void *), /* in */ int32_t l, /* in */ int32_t m, /* in */ int32_t r) {
	int32_t i = 0;
	int32_t j = 0;
	int32_t k = 0;
	int32_t n1 = m - l + 1;
	int32_t n2 = r - m;

	char* arr = (char*)first;
    char* L = (char*)pIMem->pVTbl->Alloc(pIMem, n1 * size);
    char* R = (char*)pIMem->pVTbl->Alloc(pIMem, n2 * size);

	for (i = 0; i < n1; i++) {
		*(L + i * size) = *(arr + (l + i) * size);
	}

	for (j = 0; j < n2; j++) {
		*(R + j * size) = *(arr + (m + 1 + j) * size);
	}

	i = 0;
	j = 0;
	k = l;

	while (i < n1 && j < n2) {
		if ((*cmp)((void*)(L + i * size), (void*)(R + j * size)) <= 0) {
			*(arr + k * size) = *(L + i * size);
			i++;
		} else {
			*(arr + k * size) = *(R + j * size);
			j++;
		}
		k++;
	}

	while (i < n1) {
		*(arr + k * size) = *(L + i * size);
		i++;
		k++;
	}

	while (j < n2) {
		*(arr + k * size) = *(R + j * size);
		j++;
		k++;
	}

	pIMem->pVTbl->Free(pIMem, R);
	pIMem->pVTbl->Free(pIMem, L);
}

/*
/*
 *
 * <сводка>
 *   Функция mergeSort
 * </сводка>
 *
 * <описание>
 *   Рекурсивная функция сортировки слиянием
 * </описание>
 *
 */
void mergeSort(/* in */ IEcoMemoryAllocator1* pIMem, /* in */ void* first, /* in */ int32_t size, /* in */ int16_t (*cmp) (const void *, const void *), int32_t start, int32_t end) {
	int32_t m = start + (end - start) / 2;

	if (start < end) {
		mergeSort(pIMem, first, size, cmp, start, m);
		mergeSort(pIMem, first, size, cmp, m + 1, end);
		merge(pIMem, first, size, cmp, start, m, end);
	}
}

/*
 * <сводка>
 *   Функция qsort
 * </сводка>
 *
 * <описание>
 *   Функция сортировки
 * </описание>
 *
 */

int16_t CEcoMergeSortComponent_Qsort(/* in */ struct IEcoMergeSortComponent* me, /* in */ void* first, /* in */ int32_t number, /* in */ int32_t size, /* in */ int16_t (*comparator) (const void *, const void *)) {
	CEcoMergeSortComponent* pCMe = (CEcoMergeSortComponent*)me;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

    mergeSort(pCMe->m_pIMem, first, size, comparator, 0, number - 1);
    return 0;
}

/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализации экземпляра
 * </описание>
 *
 */
int16_t initCEcoMergeSortComponent(/*in*/ struct IEcoMergeSortComponent* me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoMergeSortComponent* pCMe = (CEcoMergeSortComponent*)me;
    IEcoInterfaceBus1* pIBus = 0;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;


    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);
	
    return result;
}

/* Create Virtual Table IEcoMergeSortComponent */
IEcoMergeSortComponentVTbl g_xA301546D69774B588F18CFD8536718EDVTbl = {
    CEcoMergeSortComponent_QueryInterface,
    CEcoMergeSortComponent_AddRef,
    CEcoMergeSortComponent_Release,
    CEcoMergeSortComponent_Qsort
};

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t createCEcoMergeSortComponent(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoMergeSortComponent** ppIEcoMergeSortComponent) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoMergeSortComponent* pCMe = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;
	
    /* Проверка указателей */
    if (ppIEcoMergeSortComponent == 0 || pIUnkSystem == 0) {
        return result;
    }

    /* Получение системного интерфейса приложения */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem1, (void **)&pISys);

    /* Проверка */
    if (result != 0 && pISys == 0) {
        return result;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

	/* Получение идентификатора компонента для работы с памятью */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Получение интерфейса распределителя памяти */
    pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 && pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        pISys->pVTbl->Release(pISys);
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoMergeSortComponent*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoMergeSortComponent));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoMergeSortComponent */
    pCMe->m_pVTblIEcoMergeSortComponent = &g_xA301546D69774B588F18CFD8536718EDVTbl;

    /* Инициализация данных */
    pCMe->m_Name = 0;

    /* Возврат указателя на интерфейс */
    *ppIEcoMergeSortComponent = (IEcoMergeSortComponent*)pCMe;

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void deleteCEcoMergeSortComponent(/* in */ IEcoMergeSortComponent* pIEcoMergeSortComponent) {
    CEcoMergeSortComponent* pCMe = (CEcoMergeSortComponent*)pIEcoMergeSortComponent;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoMergeSortComponent != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}
