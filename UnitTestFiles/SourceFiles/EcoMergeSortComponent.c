/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoMergeSortComponent
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoMergeSortComponent.h"
#include "IEcoCalculatorX.h"
#include "IdEcoCalculatorA.h"
#include "IdEcoCalculatorB.h"

int16_t compare(const void * a, const void * b) {
    return (*(int32_t*)a - *(int32_t*)b);
}
/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    int32_t* arr = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoMergeSortComponent* pIEcoMergeSortComponent = 0;
	IEcoCalculatorX* g_pIX = 0;

    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem1, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#ifdef ECO_LIB
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoMergeSortComponent, (IEcoUnknown*)GetIEcoComponentFactoryPtr_195502917ABB478EA660ADE678AFF383);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#endif
    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 && pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }
	
    /* Выделение блока памяти */
    arr = (int32_t *)pIMem->pVTbl->Alloc(pIMem, 6 * sizeof(int32_t));
	
    /* Заполнение блока памяти */
	arr[0] = 12;
	arr[1] = 11;
	arr[2] = 13;
	arr[3] = 5;
	arr[4] = 6;
	arr[5] = 7;

	printf("Before: %d %d %d %d %d %d\n", arr[0], arr[1], arr[2], arr[3], arr[4], arr[5]);

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMergeSortComponent, 0, &IID_IEcoMergeSortComponent, (void**) &pIEcoMergeSortComponent);

	if (result != 0 || g_pIX == 0) {
		/* Получение интерфейса по работе со сложением и вычитанием у компонента "B" c поддержкой агрегирования */
		result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorB, 0, &IID_IEcoCalculatorX, (void**) &g_pIX);

		/* Проверка */
		if (result != 0 || g_pIX == 0) {
			/* Получение интерфейса по работе со сложением и вычитанием у компонента "A" */
			result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorA, 0, &IID_IEcoCalculatorX, (void**) &g_pIX);
			if (result != 0 || g_pIX == 0) {
				/* Освобождение интерфейсов в случае ошибки */
				goto Release;
			}
		}
	}

    if (result != 0 && pIEcoMergeSortComponent == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    result = pIEcoMergeSortComponent->pVTbl->CEcoMergeSortComponent_Qsort(pIEcoMergeSortComponent, arr, 6, sizeof(int32_t), compare);
	printf("After: %d %d %d %d %d %d\n", arr[0], arr[1], arr[2], arr[3], arr[4], arr[5]);

	result = g_pIX->pVTbl->Addition(g_pIX, 1, 3);
	printf("1 + 3 = %d", result);
	
    /* Освобождение блока памяти */
    pIMem->pVTbl->Free(pIMem, arr);

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoMergeSortComponent != 0) {
        pIEcoMergeSortComponent->pVTbl->Release(pIEcoMergeSortComponent);
    }

	if (g_pIX != 0) {
		g_pIX->pVTbl->Release(g_pIX);
	}

    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

