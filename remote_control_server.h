/*
 * Generated by erpcgen 1.9.0 on Wed Dec  7 08:24:49 2022.
 *
 * AUTOGENERATED - DO NOT EDIT
 */


#if !defined(_remote_control_server_h_)
#define _remote_control_server_h_

#ifdef __cplusplus
#include "erpc_server.h"
#include "erpc_codec.h"
extern "C"
{
#include "remote_control.h"
#include <stdint.h>
#include <stdbool.h>
}

#if 10900 != ERPC_VERSION_NUMBER
#error "The generated shim code version is different to the rest of eRPC code."
#endif


/*!
 * @brief Service subclass for remote_control.
 */
class remote_control_service : public erpc::Service
{
public:
    remote_control_service() : Service(kremote_control_service_id) {}

    /*! @brief Call the correct server shim based on method unique ID. */
    virtual erpc_status_t handleInvocation(uint32_t methodId, uint32_t sequence, erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory);

private:
    /*! @brief Server shim for remote_putc of remote_control interface. */
    erpc_status_t remote_putc_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for remote_locate of remote_control interface. */
    erpc_status_t remote_locate_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);
};

extern "C" {
#else
#include "remote_control.h"
#endif // __cplusplus

typedef void * erpc_service_t;

erpc_service_t create_remote_control_service(void);

#if ERPC_ALLOCATION_POLICY == ERPC_ALLOCATION_POLICY_DYNAMIC
void destroy_remote_control_service(erpc_service_t *service);
#elif ERPC_ALLOCATION_POLICY == ERPC_ALLOCATION_POLICY_STATIC
void destroy_remote_control_service(void);
#else
#warning "Unknown eRPC allocation policy!"
#endif

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _remote_control_server_h_
