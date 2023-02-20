/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IdEcoMergeSortComponent
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IdEcoMergeSortComponent
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

#ifndef __ID_ECOMERGESORTCOMPONENT_H__
#define __ID_ECOMERGESORTCOMPONENT_H__

#include "IEcoBase1.h"
#include "IEcoMergeSortComponent.h"

/* EcoMergeSortComponent CID = {19550291-7ABB-478E-A660-ADE678AFF383} */
#ifndef __CID_EcoMergeSortComponent
static const UGUID CID_EcoMergeSortComponent = {0x01, 0x10, 0x19, 0x55, 0x02, 0x91, 0x7A, 0xBB, 0x47, 0x8E, 0xA6, 0x60, 0xAD, 0xE6, 0x78, 0xAF, 0xF3, 0x83};
#endif /* __CID_EcoMergeSortComponent */

/* Фабрика компонента для динамической и статической компановки */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_195502917ABB478EA660ADE678AFF383;
#endif

#endif /* __ID_ECOMERGESORTCOMPONENT_H__ */
