// stdafx.h: archivo de inclusión de los archivos de inclusión estándar del sistema
// o archivos de inclusión específicos de un proyecto utilizados frecuentemente,
// pero rara vez modificados
//

#pragma once

#ifdef _WIN32

	#if _MSC_VER == 1310

	#else
		#include "targetver.h"
	#endif

    #define WIN32_LEAN_AND_MEAN             // Excluir material rara vez utilizado de encabezados de Windows
    // Archivos de encabezado de Windows:
    #include <windows.h>

#endif

#ifdef JAVI_EXTRAS
    #include <vld.h>
#endif

#include "expat.h"

#include "../depends/logger/logging.h"
#undef LOGGER
#include "../depends/logger/log_console_colored.h"
#define LOGGER core::logging::logger<core::logging::log_console_colored>