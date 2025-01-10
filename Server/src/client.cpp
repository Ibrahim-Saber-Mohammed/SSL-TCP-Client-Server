#include <iostream>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <arpa/inet.h>
#include <unistd.h>



constexpr const char* CLIENT_CERTIFICATE = "/home/ibrahim/Desktop/Sockets/Client-Server/certificates/client_csr.pem";
constexpr const char* CLIENT_PRIVATE_KEY = "/home/ibrahim/Desktop/Sockets/Client-Server/certificates/client_private_key.pem";
void initialize_openssl()
{
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
}

void cleanup_openssl()
{
    EVP_cleanup();
}

SSL_CTX *create_context()
{
    const SSL_METHOD *method;
    SSL_CTX *ctx;

    method = SSLv23_client_method();
    ctx = SSL_CTX_new(method);
    if (!ctx)
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}

void configure_context(SSL_CTX *ctx)
{
    // Load the client's certificate and private key (if needed)
    SSL_CTX_use_certificate_file(ctx, CLIENT_CERTIFICATE, SSL_FILETYPE_PEM);
    SSL_CTX_use_PrivateKey_file(ctx, CLIENT_PRIVATE_KEY, SSL_FILETYPE_PEM);
}

int main()
{
    initialize_openssl();
    SSL_CTX *ctx = create_context();
    configure_context(ctx);

    // Create a new SSL connection state object
    SSL *ssl = SSL_new(ctx);

    // Create a socket and connect to the server
    int server = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);                   // Change to your server's port
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Change to your server's IP
    std::cout << "ay 7aga------" << std::endl;
    if (connect(server, (struct sockaddr *)&addr, sizeof(addr)) != 0)
    {
        std::cerr << "Connection failed" << std::endl;
        return -1;
    }

    // Bind the SSL object with the socket
    SSL_set_fd(ssl, server);
    std::cout << "ay 7aga2------" << std::endl;
    // Perform the SSL handshake
    if (SSL_connect(ssl) <= 0)
    {
        std::cerr << "SSL handshake failed" << std::endl;
        ERR_print_errors_fp(stderr);
    }
    else
    {
        std::cout << "Connected with " << SSL_get_cipher(ssl) << std::endl;

        // Send data to the server
        const char *msg = "Hello, Server......!";
        SSL_write(ssl, msg, strlen(msg));
        const char *msg1 = "Esht8alttttttt.....!";
        auto re = SSL_write(ssl, msg1, strlen(msg1));
        std::cout << "Data sent \n";
        while(true)
        {
            re = SSL_write(ssl, msg1, strlen(msg1));
            auto er = SSL_get_error(ssl, re);
            if(re <= 0)
            {
                std::cout << "aaaaaaaaaaaa\n";
                ERR_print_errors_fp(stderr);
            }
            std::cout << "Server fd :" <<server << "\n";
        }
        // // Optionally read response from the server
        // char buffer[1024];
        // int bytes = SSL_read(ssl, buffer, sizeof(buffer) - 1);
        // if (bytes > 0) {
        //     buffer[bytes] = 0; // Null-terminate the string
        //     std::cout << "Received: " << buffer << std::endl;
        // }
    }

    // Clean up
    SSL_free(ssl);
    close(server);
    SSL_CTX_free(ctx);
    cleanup_openssl();

    return 0;
}