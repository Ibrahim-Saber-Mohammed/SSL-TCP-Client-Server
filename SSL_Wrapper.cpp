#include <openssl/ssl.h>
#include <openssl/err.h>
#include <string>
#include <memory>
#include <unistd.h>

class SSL_Wrapper {
public:
    SSL_Wrapper(int fd) : m_ssl(nullptr), m_fd(fd) {
    { // Initialize the SSL object with the shared context 
       std::unique_ptr<SSL, decltype(&SSL_free)> ssl_ptr(SSL_new(get_context().get()), &SSL_free);
       m_ssl = std::move(ssl_ptr);
       SSL_set_fd(m_ssl, fd);
    }

    ~SSL_Wrapper() {
        if (m_ssl) SSL_free(m_ssl);
        if (m_fd >= 0) close(m_fd);
    }

    bool do_handshake() {
        return SSL_accept(m_ssl) > 0;
    }

    int send(const char* data, size_t length) {
        return SSL_write(m_ssl, data, length);
    }

    int receive(char* buffer, size_t length) {
        return SSL_read(m_ssl, buffer, length);
    }

    int get_fd() const { return SSL_get_fd(m_ssl); }

    static std::shared_ptr<SSL_CTX>& get_context() {
        static std::shared_ptr<SSL_CTX> context = create_context();
        return context;
    }
private:
    std::unique_ptr<SSL, decltype(&SSL_free)> m_ssl{nullptr,&SSL_free};
    int m_fd;
    static std::shared_ptr<SSL_CTX> create_context() {
        SSL_CTX* ctx = SSL_CTX_new(SSLv23_server_method());
        if (!ctx) {
            fprintf(stderr, "Unable to create SSL context\n");
            ERR_print_errors_fp(stderr);
            exit(EXIT_FAILURE);
        }
        SSL_CTX_set_cipher_list(ctx, "HIGH:!aNULL:!MD5"); // Example cipher suite configuration
        if (SSL_CTX_use_certificate_file(ctx, "server_cert.pem", SSL_FILETYPE_PEM) <= 0) {
            ERR_print_errors_fp(stderr);
            exit(EXIT_FAILURE);
        }
        if (SSL_CTX_use_PrivateKey_file(ctx, "server_private_key.pem", SSL_FILETYPE_PEM) <= 0) {
            ERR_print_errors_fp(stderr);
            exit(EXIT_FAILURE);
        }
        if (!SSL_CTX_check_private_key(ctx)) {
            fprintf(stderr, "Private key does not match the public certificate\n");
            exit(EXIT_FAILURE);
        }
        return std::shared_ptr<SSL_CTX>(ctx, SSL_CTX_free);
    }
};
}
