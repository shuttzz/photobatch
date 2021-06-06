#include <iostream>
#include <iomanip>
#include <map>

class ArgumentParser
{
public:
    void RegisterFlag(const std::string& flag)
    {
        if (!flag.empty())
        {
            m_Flags[flag] = false;
        }
    }

    bool GetFlag(const std::string& flag) const
    {
        if (!flag.empty())
        {
            // Esse código é como se trabalhava no c++ antes da versão 11 para trabalhar com interator
            // std::map<std::string, bool>::iterator flagIt = m_Flags.find(flag);

            // Agora após a versão 11 posso utilizar o código abaixo
            auto flagIt = m_Flags.find(flag);
            if (flagIt != std::end(m_Flags))
            {
                // Aqui eu retornaria a chave desse map
                // return flagIt->first;

                // Aqui utilizando o second eu retorno o valor da chave passada no find
                return flagIt->second;
            }
        }
        return false;
    }

    void Parse(int argc, char* argv[])
    {
        if (argc > 1)
        {
            for (int i = 1; i < argc; ++i) {
                std::string arg = argv[i];

                if (arg.length() >= 3)
                {
                    // Aqui verificamos se possui o prefixo --
                    if (arg[0] == '-' && arg[1] == '-')
                    {
                        arg = arg.substr(2);

                        if (arg.find_first_of('=') != std::string::npos)
                        {
                            // Aqui cai quando é uma opção
                        }
                        else
                        {
                            // É uma flag
                            auto flagIt = m_Flags.find(arg);
                            if (flagIt != std::end(m_Flags))
                            {
                                flagIt->second = true;
                            }
                        }
                    }
                }
            }
        }
    }

private:
    std::map<std::string, bool> m_Flags;
};

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "pt_BR");

    ArgumentParser argParser;
    argParser.RegisterFlag("rename");
    argParser.RegisterFlag("convert");
    argParser.RegisterFlag("resize");
    argParser.RegisterFlag("scale");

    argParser.Parse(argc, argv);

    std::cout << std::boolalpha << "Rename  : " << argParser.GetFlag("rename") << std::endl;
    std::cout << std::boolalpha << "Convert : " << argParser.GetFlag("convert") << std::endl;
    std::cout << std::boolalpha << "Resize  : " << argParser.GetFlag("resize") << std::endl;
    std::cout << std::boolalpha << "Scale   : " << argParser.GetFlag("scale") << std::endl;

    return 0;
}