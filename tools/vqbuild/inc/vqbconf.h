/*
Copyright 2026 dywoq - Apache License 2.0
https://github.com/dywoq/vacui

Description:

    Config management, parsing and its type definitions

*/

#ifndef _VQBCONF_H
#define _VQBCONF_H

#include <exception>
#include <string>

namespace vqbuild
{
    namespace config
    {
        struct ConfigField
        {
            virtual ~ConfigField()
            {
            }

            virtual const std::string
            GetName() const = 0;

            virtual bool
            IsRequired() const throw() = 0;
        };

        struct TargetConfigField : public ConfigField
        {
            const std::string
            GetName() const
            {
                return "TARGET";
            }

            bool
            IsRequired() const throw()
            {
                return true;
            }
        };

        struct KindConfigField : public ConfigField
        {
            const std::string
            GetName() const
            {
                return "KIND";
            }

            bool
            IsRequired() const throw()
            {
                return true;
            }
        };

        struct SourcesConfigField : public ConfigField
        {
            const std::string
            GetName() const
            {
                return "SOURCES";
            }

            bool
            IsRequired() const throw()
            {
                return true;
            }
        };

        struct DependenciesConfigField : public ConfigField
        {
            const std::string
            GetName() const
            {
                return "DEPENDENCIES";
            }

            bool
            IsRequired() const throw()
            {
                return true;
            }
        };

        struct BuildDirConfigField : public ConfigField
        {
            const std::string
            GetName() const
            {
                return "BUILD_DIR";
            }

            bool
            IsRequired() const throw()
            {
                return true;
            }
        };

        struct ObjectsDirConfigField : public ConfigField
        {
            const std::string
            GetName() const
            {
                return "OBJECTS_DIR";
            }

            bool
            IsRequired() const throw()
            {
                return true;
            }
        };

        /*
        Description:

            Exception class, thrown by config management functions
        
        */
        class ConfigException : public std::exception
        {
            std::string str_;

          public:
            virtual ~ConfigException() throw();
            ConfigException(const std::string &msg);
            ConfigException(const char *msg);

            const char *
            what() const throw();
        };
    } // namespace config
} // namespace vqbuild

#endif
