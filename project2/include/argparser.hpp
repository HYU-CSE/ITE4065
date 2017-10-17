#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

namespace arg {
    class Parser {
    public:
        Parser() {
            add("app", "caller");
        }

        size_t argument(const std::string& name, const std::string& description="") {
            return add(name, description);
        }

        bool parse(int argc, char * argv[]) {
            std::vector<std::string> args = std::vector<std::string>(argv, argv + argc);
            
            for (auto it = args.begin(); it != args.end(); ++it) {
                size_t index = std::distance(args.begin(), it);
                emplace(index, *it);
            }

            return true;
        }

        template <typename T>
        T get(const std::string& name) {
            T value;
            std::stringstream ss(values[index(name)]);
            ss >> value;
            return value;
        }

    private:
        std::unordered_map<std::string, size_t> indicies;
        std::vector<std::string> descriptions;
        std::vector<std::string> values;

        size_t add(const std::string& name, const std::string& description) {
            indicies[name] = values.size();
            values.emplace_back();
            descriptions.emplace_back(description);
            return indicies[name];
        }

        void emplace(size_t index, const std::string& value) {
            if (index >= values.size()) {
                values.emplace_back(value);
            } else {
                values[index] = value;
            }
        }

        size_t index(const std::string& name) {
            if (indicies.find(name) == indicies.end()) throw std::out_of_range("key not exist");
            return indicies.at(name);
        }
    };
}

#endif
