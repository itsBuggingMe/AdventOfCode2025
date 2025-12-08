#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

#include "Day.cpp"

struct float3
{
    float X;
    float Y;
    float Z;

    float squared_distance_to(float3 other)
    {
        float acc = 0;
        acc += (other.X - X) * (other.X - X);
        acc += (other.Y - Y) * (other.Y - Y);
        acc += (other.Z - Z) * (other.Z - Z);
        return acc;
    }

    bool operator()(const float3& a, const float3& b) const
    {
        return a.X == b.X && a.Y == b.Y && a.Z == b.Z;
    }

    size_t operator()(const float3& a) const
    {
        return std::hash<float>{}(a.X) * 13
            ^ std::hash<float>{}(a.Y) * 13
            ^ std::hash<float>{}(a.Z);
    }
};

struct float3x2
{
    float3 A;
    float3 B;
    float Distance;
};


class Day8 : public Day
{
public:
    std::int32_t day_num() override
    {
        return 8;
    }

    int32_t floodfill(
        std::unordered_set<float3, float3, float3>& visited,
        std::unordered_map<float3, std::vector<float3>, float3, float3>& edges,
        float3 position)
    {
        int32_t nodeCount = 0;
        for (float3 across : edges[position])
        {
            if (visited.count(across))
                continue;

            visited.insert(across);
            nodeCount += floodfill(visited, edges, across);
        }
        return nodeCount + 1; // + 1 for self
    }


    std::string part1(std::istream& input) override
    {
        std::string line;
        std::vector<float3> junctions;
        while (std::getline(input, line))
        {
            int32_t f = line.find(',');
            int32_t l = line.find_last_of(',');

            float3 pos =
            {
                .X = std::stof(line.substr(0, f)),
                .Y = std::stof(line.substr(f + 1, l - f - 1)),
                .Z = std::stof(line.substr(l + 1))
            };

            junctions.push_back(pos);
        }

        std::vector<float3x2> combinations;

        for (int32_t i = 0; i < junctions.size(); i++)
        {
            for (int32_t j = i + 1; j < junctions.size(); j++)
            {
                combinations.push_back(float3x2
                    {
                        .A = junctions[i],
                        .B = junctions[j],
                        .Distance = junctions[i].squared_distance_to(junctions[j])
                    });
            }
        }

        std::sort(combinations.begin(), combinations.end(), [](float3x2 a, float3x2 b) {
            return a.Distance < b.Distance;
        });

        std::unordered_map<float3, std::vector<float3>, float3, float3> edges;

        // connect 1000 shortest connections
        for (int32_t i = 0; i < 1000; i++)
        {
            edges[combinations[i].A].push_back(combinations[i].B);
            edges[combinations[i].B].push_back(combinations[i].A);
        }


        std::unordered_set<float3, float3, float3> visited;

        std::vector<int32_t> networkSizes;
        for (float3 junction : junctions)
        {
            networkSizes.push_back(floodfill(visited, edges, junction));
        }
        std::sort(networkSizes.begin(), networkSizes.end());

        int32_t networkCount = networkSizes.size();

        return std::to_string(
            (int64_t)(networkSizes[networkCount - 1] - 1) *
            (int64_t)(networkSizes[networkCount - 2] - 1) *
            (int64_t)(networkSizes[networkCount - 3] - 1));
    }

    std::string part2(std::istream& input) override
    {
        std::string line;
        std::vector<float3> junctions;
        while (std::getline(input, line))
        {
            int32_t f = line.find(',');
            int32_t l = line.find_last_of(',');

            float3 pos =
            {
                .X = std::stof(line.substr(0, f)),
                .Y = std::stof(line.substr(f + 1, l - f - 1)),
                .Z = std::stof(line.substr(l + 1))
            };

            junctions.push_back(pos);
        }

        std::vector<float3x2> combinations;

        for (int32_t i = 0; i < junctions.size(); i++)
        {
            for (int32_t j = i + 1; j < junctions.size(); j++)
            {
                combinations.push_back(float3x2
                    {
                        .A = junctions[i],
                        .B = junctions[j],
                        .Distance = junctions[i].squared_distance_to(junctions[j])
                    });
            }
        }

        std::sort(combinations.begin(), combinations.end(), [](float3x2 a, float3x2 b) {
            return a.Distance < b.Distance;
        });


        uint32_t mul = 0;

        std::unordered_set<float3, float3, float3> visited;
        std::unordered_map<float3, std::vector<float3>, float3, float3> edges;
        int32_t i = 0;
        while (junctions.size() != visited.size())
        {
            edges[combinations[i].A].push_back(combinations[i].B);
            edges[combinations[i].B].push_back(combinations[i].A);

            mul = (uint32_t)combinations[i].B.X * (uint32_t)combinations[i].A.X;
            visited.clear();
            floodfill(visited, edges, junctions[0]);
            i++;
        }

        return std::to_string(mul);
    }
};