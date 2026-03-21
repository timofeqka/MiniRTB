//model structure json
#pragma once 

#include <vector>
#include <string>
#include <nlohmann/json.hpp>


namespace minirtb::domain {
    struct  Campaign {
        int id{};
        std::string name;
        double budget{};
        bool active{};
        std::vector<std::string> tags;
    };

    inline void to_json(nlohmann::json& j, const Campaign& c) {
        j = nlohmann::json{
            {"id", c.id},
            {"name", c.name},
            {"budget", c.budget},
            {"active", c.active},
            {"tags", c.tags}
        };
    }

    inline void from_json(const nlohmann::json& j, Campaign& c) {
        j.at("id").get_to(c.id);
        j.at("name").get_to(c.name);
        j.at("budget").get_to(c.budget);
        j.at("active").get_to(c.active);
        j.at("tags").get_to(c.tags);
    }
}
