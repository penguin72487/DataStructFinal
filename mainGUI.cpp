#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <sstream>
#include <iostream>

#define FRONT_COLOUR sf::Color::Black
#define BACK_COLOUR sf::Color::White

#define IMG_HEIGHT 555
#define IMG_WIDTH 1920

#define FILENAME "B9"

//讀取.exe同目錄下的 FILENAME.txt檔案



int daysSinceEpoch(int date) {
    struct tm time_in = { 0, 0, 0, date % 100, (date / 100) % 100 - 1, date / 10000 - 1900 };
    time_t tmp_t = mktime(&time_in);
    const time_t epoch = 0;
    return difftime(tmp_t, epoch) / (86400);//=60 * 60 * 24
}

sf::VertexArray createXYLine(const std::vector<sf::Vector2f>& points) {
    sf::VertexArray lines(sf::LinesStrip, points.size());
    std::vector<sf::Vector2f> continuousPoints = points;
    int minDays = daysSinceEpoch(static_cast<int>(points[0].x));

    for (auto& point : continuousPoints) {
        point.x = static_cast<float>(daysSinceEpoch(static_cast<int>(point.x)) - minDays);
    }

    float minX = std::min_element(continuousPoints.begin(), continuousPoints.end(), [](sf::Vector2f a, sf::Vector2f b) { return a.x < b.x; })->x;
    float maxX = std::max_element(continuousPoints.begin(), continuousPoints.end(), [](sf::Vector2f a, sf::Vector2f b) { return a.x < b.x; })->x;
    float minY = std::min_element(continuousPoints.begin(), continuousPoints.end(), [](sf::Vector2f a, sf::Vector2f b) { return a.y < b.y; })->y;
    float maxY = std::max_element(continuousPoints.begin(), continuousPoints.end(), [](sf::Vector2f a, sf::Vector2f b) { return a.y < b.y; })->y;

    for (size_t i = 0; i < continuousPoints.size(); ++i) {
        float normalizedX = (continuousPoints[i].x - minX) / (maxX - minX);
        float normalizedY = (continuousPoints[i].y - minY) / (maxY - minY);

        float xPos = 50 + normalizedX * (IMG_WIDTH - 100);
        float yPos = IMG_HEIGHT - 50 - normalizedY * (IMG_HEIGHT - 100);

        lines[i].position = sf::Vector2f(xPos, yPos);
        lines[i].color = FRONT_COLOUR;
    }

    return lines;
}

sf::VertexArray createAxes() {
    sf::VertexArray axes(sf::Lines, 4);
    axes[0].position = sf::Vector2f(50, IMG_HEIGHT - 50);
    axes[1].position = sf::Vector2f(IMG_WIDTH - 50, IMG_HEIGHT - 50);
    axes[2].position = sf::Vector2f(50, IMG_HEIGHT - 50);
    axes[3].position = sf::Vector2f(50, 50);

    for (int i = 0; i < 4; ++i) {
        axes[i].color = FRONT_COLOUR;
    }

    return axes;
}

void createLabels(sf::RenderTexture& texture, const sf::Font& font, const std::vector<sf::Vector2f>& points) {
    std::vector<sf::Vector2f> continuousPoints = points;
    int minDays = daysSinceEpoch(static_cast<int>(points[0].x));

    for (auto& point : continuousPoints) {
        point.x = static_cast<float>(daysSinceEpoch(static_cast<int>(point.x)) - minDays);
    }

    float minX = std::min_element(continuousPoints.begin(), continuousPoints.end(), [](sf::Vector2f a, sf::Vector2f b) { return a.x < b.x; })->x;
    float maxX = std::max_element(continuousPoints.begin(), continuousPoints.end(), [](sf::Vector2f a, sf::Vector2f b) { return a.x < b.x; })->x;
    float minY = std::min_element(continuousPoints.begin(), continuousPoints.end(), [](sf::Vector2f a, sf::Vector2f b) { return a.y < b.y; })->y;
    float maxY = std::max_element(continuousPoints.begin(), continuousPoints.end(), [](sf::Vector2f a, sf::Vector2f b) { return a.y < b.y; })->y;

    for (int i = 0; i <= 10; ++i) {
        float xValue = minX + i * (maxX - minX) / 10;
        int dateValue = minDays + static_cast<int>(xValue);
        time_t rawtime = dateValue * 86400;
        struct tm * dt;
        char buffer[30];
        dt = localtime(&rawtime);
        strftime(buffer, sizeof(buffer), "%Y%m%d", dt);
        sf::Text label(buffer, font, 15);
        label.setFillColor(FRONT_COLOUR);
        label.setPosition(50 + i * (IMG_WIDTH - 100) / 10, IMG_HEIGHT - 40);
        texture.draw(label);
    }

    for (int i = 0; i <= 10; ++i) {
        float yValue = minY + i * (maxY - minY) / 10;
        sf::Text label(std::to_string(static_cast<int>(yValue)), font, 15);
        label.setFillColor(FRONT_COLOUR);
        label.setPosition(10, IMG_HEIGHT - 50 - i * (IMG_HEIGHT - 100) / 10 - 10);
        texture.draw(label);
    }
}

std::vector<sf::Vector2f> readDataFromFile() {
    std::vector<sf::Vector2f> dataPoints;
    std::ifstream file(FILENAME".txt");
    if (!file.is_open()) {
        std::cerr << "Open file" << FILENAME".txt" <<"failed\n" ;
        return dataPoints;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        float x, y;
        if (!(iss >> x >> y)) {
            break;
        }
        dataPoints.emplace_back(x, y);
    }

    file.close();
    return dataPoints;
}


int main() {
    sf::RenderTexture texture;
    if (!texture.create(IMG_WIDTH, IMG_HEIGHT)) {
        return -1;
    }

    sf::Font font;
    if (!font.loadFromFile("Font.ttf")) {
        return -2;
    }

    std::vector<sf::Vector2f> dataPoints = readDataFromFile(  );
    if (dataPoints.empty()) {
        return -3;
    }

    sf::VertexArray polyline = createXYLine(dataPoints);
    sf::VertexArray axes = createAxes();

    texture.clear(BACK_COLOUR);
    texture.draw(polyline);
    texture.draw(axes);
    createLabels(texture, font, dataPoints);
    texture.display();

    sf::Texture resultTexture = texture.getTexture();
    sf::Image screenshot = resultTexture.copyToImage();
    if (!screenshot.saveToFile(FILENAME".png")) {
        return -4;
    }
    return 0;
}
