#include <stdlib.h>
namespace NETWORK{

    class Commands{
        public:
        void openFireFox(void) const noexcept;
        void openFacebook(void)const noexcept;
        void openYoutube(void)const noexcept;
        void openLinkedin(void)const noexcept;
        void openGithub(void)const noexcept;
        void openVSCode(void)const noexcept;
        void openWhatsapp(void)const noexcept;
        void openCalculator(void)const noexcept;
        void openTelegram(void)const noexcept;
    };
    void Commands::openFacebook(void)const noexcept{
    // Open Facebook
        system("xdg-open https://www.facebook.com");
    }

    void Commands::openYoutube()const noexcept{
        // Open YouTube
        system("xdg-open https://www.youtube.com");
    }

    void Commands::openWhatsapp()const noexcept{
        // Open WhatsApp Web
        system("xdg-open https://web.whatsapp.com");
    }

    void Commands::openLinkedin()const noexcept{
        // Open LinkedIn
        system("xdg-open https://www.linkedin.com");
    }

    void Commands::openGithub()const noexcept{
        // Open GitHub
        system("xdg-open https://github.com");
    }

    void Commands::openCalculator()const noexcept{
        // Open Calculator
        system("gnome-calculator");
    }

    void Commands::openVSCode()const noexcept{
            // Open VS Code
        system("code .");
    }

    void Commands::openTelegram() const noexcept{
        system("xdg-open https://web.telegram.org/");
    }

}