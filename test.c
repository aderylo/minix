#include <lib.h>
#include <minix/rs.h>

int main()
{
        message m;
        endpoint_t ipc_ep;
        minix_rs_lookup("pm", &ipc_ep);
        _syscall(ipc_ep, PM_PRINTMESSAGE, &m);
}
