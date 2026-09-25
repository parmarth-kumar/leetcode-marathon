#include <string>
using namespace std;

class SolutionBaseline {
public:
    bool isValid(string s) {
        size_t len;
        do {
            len = s.length();
            size_t pos;
            if ((pos = s.find("()")) != string::npos) s.erase(pos, 2);
            else if ((pos = s.find("{}")) != string::npos) s.erase(pos, 2);
            else if ((pos = s.find("[]")) != string::npos) s.erase(pos, 2);
        } while (s.length() < len);
        return s.empty();
    }
};
