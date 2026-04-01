//demo code
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <filesystem>

#include <nlohmann/json.hpp>
#include "minirtb/domain/campaign.hpp"

using json = nlohmann::json;
using minirtb::domain::Campaign;

std::vector<Campaign> load_campaigns(const std::string& filename) {
    std::ifstream input(filename);
    if (!input.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
}

    json j;
    input >> j;

    return j.get<std::vector<Campaign>>();
}

void save_campaigns(const std::string& filename, 
                    const std::vector<Campaign>& campaigns) 
{
    std::ofstream output(filename);
    if (!output.is_open()) {
        throw std::runtime_error("Failed to write file: " + filename);
    }

    json j = campaigns;
    output << std::setw(4) << j << "\n";
}

void print_campaigns(const std::vector<Campaign>& campaigns) {
    std::cout << "Campaign list:\n\n";

    for (const auto& campaign : campaigns) {
        std::cout << "ID: " << campaign.get_id() << "\n";
        std::cout << "Name: " << campaign.get_name() << "\n";
        std::cout << "Budget: " << campaign.get_budget() << "\n";
        std::cout << "Active: " << (campaign.is_active() ? "true" : "false") << "\n";
        std::cout << "Tags: ";

        for (const auto& tag : campaign.get_tags()) {
            std::cout << tag << ' ';
        }

        std::cout << "\n-------------------------\n";
    }
}


int main() {
    std::cout << "Current path: " << std::filesystem::current_path() << '\n';
    const std::string filename = "../../../../configs/campaigns/campaigns.json";

    try {
        std::vector<Campaign> campaigns = load_campaigns(filename);

        std::cout << "Loaded campaigns successfully.\n\n";
        print_campaigns(campaigns);

        Campaign new_campaign{
            4, 
            "Smartphone Launch Campaign",
            1800.0,
            true,
            {"smartphone", "electronics", "mobile"}
        };

        campaigns.push_back(new_campaign);

        std::cout << "\nNew campaign added:\n";
        std::cout << new_campaign.get_name() << "\n\n";

        save_campaigns(filename, campaigns);

        std::cout << "Updated campaigns saved to JSON file.\n";
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}