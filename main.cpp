#include "ServerSocket.hpp"
#include "Utilities.hpp"
#include "Server.hpp"
#include <sys/select.h>

void init_openssl(void)
{
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
}
void cleanup_openssl(void)
{
    EVP_cleanup();
}
SSL_CTX *create_context(void)
{
    const SSL_METHOD *method;
    method = SSLv23_server_method();
    static SSL_CTX *ctx = SSL_CTX_new(method);
    if (!ctx)
    {
        ERROR("unable to create ssl context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    // Set the cipher suite
    SSL_CTX_set_cipher_list(ctx, "HIGH:!aNULL:!MD5"); // Example cipher suite configuration
    // Load the server certificate
    if (SSL_CTX_use_certificate_file(ctx, "server_cert.pem", SSL_FILETYPE_PEM) <= 0)
    {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    // Load the server private key
    if (SSL_CTX_use_PrivateKey_file(ctx, "server_private_key.pem", SSL_FILETYPE_PEM) <= 0)
    {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    // Verify that the private key matches the certificate
    if (!SSL_CTX_check_private_key(ctx))
    {
        fprintf(stderr, "Private key does not match the public certificate\n");
        exit(EXIT_FAILURE);
    }
    return ctx;
}

int main(int argc, char *argv[])
{
    init_openssl();
    SSL_CTX *ctx = create_context();
    NETWORK::TCP_Server server(ctx, "127.0.0.1", 8080);

    server.run();

    cleanup_openssl();
    return 0;
}