#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <ctime>

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Queue_" << time(0) << endl;
        return 1;
    }

    string filename = argv[1];

    // Strip the file extension
    size_t ext_pos = filename.find_last_of(".");
    if (ext_pos != string::npos) {
        filename = filename.substr(0, ext_pos);
    }

    // Replace dots and underscores with spaces to unify the string for parsing
    replace(filename.begin(), filename.end(), '.', ' ');
    replace(filename.begin(), filename.end(), '_', ' ');

    // Regex: Matches Title (Group 1), Year (Group 2), and Resolution (Group 3)
    regex pattern(R"((.*?)\s*[\(\[]?((?:19|20)\d{2})[\)\]]?.*\b(720p|1080p|2160p|4k|4K)\b)", regex_constants::icase);
    smatch match;

    if (regex_search(filename, match, pattern)) {
        string title = match[1];
        string year = match[2];
        string res = match[3];

        // Trim leading and trailing spaces from the title
        title = regex_replace(title, regex("^\\s+|\\s+$"), "");
        // Replace internal spaces with dots
        title = regex_replace(title, regex("\\s+"), ".");

        // Force resolution to lowercase (e.g., 4K -> 4k) for consistency
        transform(res.begin(), res.end(), res.begin(), ::tolower);

        cout << title << "." << year << "." << res << endl;
    } else {
        // Failsafe: If the file has no year/resolution metadata, fall back to timestamp
        cout << "Queue_" << time(0) << endl;
    }

    return 0;
}
