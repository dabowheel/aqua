#ifndef AQUA_WIN32_H
#define AQUA_WIN32_H

#ifdef WIN32
#define EXPORT __declspec (dllexport)
#else
#define EXPORT
#endif

#endif
