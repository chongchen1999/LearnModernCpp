#include <iostream>
#include <locale>
#include <string>
#include <algorithm>

enum Season { spring, summer, fall, winter };

class Season_io : public std::locale::facet {
public:
    Season_io(size_t i = 0) : std::locale::facet{i} {}
    ~Season_io() {}
    virtual const std::string& to_str(Season x) const = 0;
    virtual bool from_str(const std::string& s, Season& x) const = 0;
    static std::locale::id id;
};

std::locale::id Season_io::id;

class US_season_io : public Season_io {
    static const std::string seasons[];
public:
    const std::string& to_str(Season) const;
    bool from_str(const std::string&, Season&) const;
};

const std::string US_season_io::seasons[] = {
    "spring",
    "summer",
    "fall",
    "winter"
};

const std::string& US_season_io::to_str(Season x) const {
    if (x < spring || winter < x) {
        static const std::string ss = "no - such - season";
        return ss;
    }
    return seasons[x];
}

bool US_season_io::from_str(const std::string& s, Season& x) const {
    const std::string* p = std::find(std::begin(seasons), std::end(seasons), s);
    if (p == std::end(seasons))
        return false;
    x = Season(p - std::begin(seasons));
    return true;
}

std::ostream& operator<<(std::ostream& os, Season x) {
    std::locale loc{ os.getloc() };
    if (std::has_facet<Season_io>(loc))
        return os << std::use_facet<Season_io>(loc).to_str(x);
    return os << static_cast<int>(x);
}

std::istream& operator>>(std::istream& is, Season& x) {
    const std::locale& loc{ is.getloc() };
    if (std::has_facet<Season_io>(loc)) {
        const Season_io& f{ std::use_facet<Season_io>(loc) };
        std::string buf;
        if (!(is >> buf && f.from_str(buf, x)))
            is.setstate(std::ios_base::failbit);
        return is;
    }
    int i;
    is >> i;
    x = static_cast<Season>(i);
    return is;
}

int main() {
    Season x;
    std::cin >> x;
    std::cout << x << std::endl;
    std::locale loc(std::locale(), new US_season_io{});
    std::cout.imbue(loc);
    std::cin.imbue(loc);
    std::cin >> x;
    std::cout << x << std::endl;
    return 0;
}