//model structure json
#pragma once 

#include <vector>
#include <string>
#include <nlohmann/json.hpp>


namespace minirtb::domain {
    

    class Campaign {
    private:
        int id{};
        std::string name;
        double budget{};
        bool active{};
        std::vector<std::string> tags;

    public:

        Campaign() = default;

        Campaign(int i, const std::string& n, double b, bool a, const std::vector<std::string>& t)
            : id(i), name(n), budget(b), active(a), tags(t) {
                if (budget <= 0) {
                    budget = 0;
                    active = false;
                }
                if (name.empty()) {
                    name = "Unnamed";
                }
        }

        int get_id() const {
            return id;
        }

        const std::string& get_name() const {
            return name;
        }

        double get_budget() const {
            return budget;
        }

        bool is_active() const {
            return active;
        }

        const std::vector<std::string>& get_tags() const {
            return tags;
        }

        void set_tags(const std::vector<std::string>& t) {
            tags = t;
        }

        void add_tags(const std::string& tag) {
            if(!tag.empty()){
                tags.push_back(tag);
            }
        }

        void set_name(const std::string& n) {
            if (!n.empty()){
                name = n;
            }
        }

        void set_budget(double b) {
            if (b >= 0) {
                budget = b;
                active = (budget > 0);
            }
        }

        void activate() {
            if (budget > 0) {
                active = true;
            }
        }

        void deactivate() {
            active = false;
        }
        
    };

    inline void to_json(nlohmann::json& j, const Campaign& c) {
        j = nlohmann::json{
            {"id", c.get_id()},
            {"name", c.get_name()},
            {"budget", c.get_budget()},
            {"active", c.is_active()},
            {"tags", c.get_tags()}
        };
    }

    inline void from_json(const nlohmann::json& j, Campaign& c) {
        int id;
        std::string name;
        double budget;
        bool active;
        std::vector<std::string> tags;

        j.at("id").get_to(id);
        j.at("name").get_to(name);
        j.at("budget").get_to(budget);
        j.at("active").get_to(active);
        j.at("tags").get_to(tags);

        c = Campaign(id, name, budget, active, tags);
    }
}
