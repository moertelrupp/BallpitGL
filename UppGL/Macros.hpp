#pragma once

// Data Structures
#define Array std::vector
#define Map std::map

// Macros
#define NULL_COPY_AND_ASSIGN(x) x(const x&) = delete;\
                                x& operator=(const x&) = delete;

#define SHUTDOWN_AND_DELETE_OBJ(x) if (x)             \
                                   {                  \
                                      x->shutdown();  \
                                      delete x;       \
                                      x = nullptr;    \
                                   }                  

#define DELETE_OBJ(x) if (x)             \
                      {                  \
                         delete x;       \
                         x = nullptr;    \
                      }     

#define NULL_ENTITY_HANDLE nullptr

#define THROW_EXCEPTION(msg) throw UppException(msg, __FILE__, __LINE__)
#define PROPAGATE_EXCEPTION(exception, msg) exception.propagate(msg, __FILE__, __LINE__); throw exception