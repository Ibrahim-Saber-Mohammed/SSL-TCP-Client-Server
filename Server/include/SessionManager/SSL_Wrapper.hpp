#include <openssl/ssl.h>
#include <openssl/err.h>
#include <string>
#include <memory>
#include <unistd.h>
#include <iostream>
namespace NETWORK
{
    constexpr const char* SERVER_CERTIFICATE = "/home/ibrahim/Desktop/Sockets/Client-Server/certificates/server_cert.pem";
    constexpr const char* SERVER_PRIVATE_KEY = "/home/ibrahim/Desktop/Sockets/Client-Server/certificates/server_private_key.pem";
    class SSL_Context
    {
    public:
        static SSL_Context &get_instance()
        {
            static SSL_Context instance;
            return instance;
        }
        std::shared_ptr<SSL_CTX> get_context()
        {
            if (!context_)
            {
                context_ = create_context();
            }
            return context_;
        }

        SSL_Context(const SSL_Context &) = delete;
        SSL_Context &operator=(const SSL_Context &) = delete;
    private:
        SSL_Context() = default;
        std::shared_ptr<SSL_CTX> context_;
        std::shared_ptr<SSL_CTX> create_context()
        {
            SSL_CTX *ctx = SSL_CTX_new(SSLv23_server_method());
            if (!ctx)
            {
                fprintf(stderr, "Unable to create SSL context\n");
                ERR_print_errors_fp(stderr);
                exit(EXIT_FAILURE);
            }
            SSL_CTX_set_cipher_list(ctx, "HIGH:!aNULL:!MD5"); // Example cipher suite configuration
            if (SSL_CTX_use_certificate_file(ctx, SERVER_CERTIFICATE, SSL_FILETYPE_PEM) <= 0)
            {
                ERR_print_errors_fp(stderr);
                exit(EXIT_FAILURE);
            }
            if (SSL_CTX_use_PrivateKey_file(ctx, SERVER_PRIVATE_KEY, SSL_FILETYPE_PEM) <= 0)
            {
                ERR_print_errors_fp(stderr);
                exit(EXIT_FAILURE);
            }
            if (!SSL_CTX_check_private_key(ctx))
            {
                fprintf(stderr, "Private key does not match the public certificate\n");
                exit(EXIT_FAILURE);
            }
            return std::shared_ptr<SSL_CTX>(ctx, SSL_CTX_free);
        }
    };
    class SSL_Wrapper
    {
    public:
        SSL_Wrapper(int fd) : m_fd(fd)
        {
            // Initialize the SSL object with the shared context
            std::unique_ptr<SSL, decltype(&SSL_free)> ssl_ptr(SSL_new(this->get_context().get()), &SSL_free);
            m_ssl = std::move(ssl_ptr);
            SSL_set_fd(m_ssl.get(), fd);
        }
        ~SSL_Wrapper()
        {
            if (m_ssl)
                SSL_shutdown(m_ssl.get());
                SSL_free(m_ssl.get());
            if (m_fd >= 0)
                close(m_fd);
        }

        bool do_handshake()
        {
            return SSL_accept(m_ssl.get()) > 0;
        }
        int send(const char *data, size_t length)
        {
            return SSL_write(m_ssl.get(), data, length);
        }
        int receive(char *buffer, size_t length)
        {
            return SSL_read(m_ssl.get(), buffer, length);
        }
        int get_fd() const { return SSL_get_fd(m_ssl.get()); }
        static std::shared_ptr<SSL_CTX> &get_context()
        {
            static std::shared_ptr<SSL_CTX> context = SSL_Context::get_instance().get_context();
            return context;
        }
    private:
        std::unique_ptr<SSL, decltype(&SSL_free)> m_ssl{nullptr, &SSL_free};
        int m_fd;
    };
    
}
