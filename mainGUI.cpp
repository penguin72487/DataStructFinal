#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>

int daysSinceEpoch(int date) {
    struct tm time_in = { 0, 0, 0, date % 100, (date / 100) % 100 - 1, date / 10000 - 1900 };
    time_t time_temp = mktime(&time_in);

    const time_t epoch = 0;
    return difftime(time_temp, epoch) / (60 * 60 * 24);
}

sf::VertexArray createPolyline(const std::vector<sf::Vector2f>& points, float width, float height) {
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

        float xPos = 50 + normalizedX * (width - 100);
        float yPos = height - 50 - normalizedY * (height - 100);

        lines[i].position = sf::Vector2f(xPos, yPos);
        lines[i].color = sf::Color::White;
    }

    return lines;
}

sf::VertexArray createAxes(float width, float height) {
    sf::VertexArray axes(sf::Lines, 4);

    axes[0].position = sf::Vector2f(50, height - 50);
    axes[1].position = sf::Vector2f(width - 50, height - 50);

    axes[2].position = sf::Vector2f(50, height - 50);
    axes[3].position = sf::Vector2f(50, 50);

    for (int i = 0; i < 4; ++i) {
        axes[i].color = sf::Color::White;
    }

    return axes;
}

void createLabels(sf::RenderWindow& window, float width, float height, const sf::Font& font, const std::vector<sf::Vector2f>& points) {
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
        label.setFillColor(sf::Color::White);
        label.setPosition(50 + i * (width - 100) / 10, height - 40);
        window.draw(label);
    }

    for (int i = 0; i <= 10; ++i) {
        float yValue = minY + i * (maxY - minY) / 10;
        sf::Text label(std::to_string(static_cast<int>(yValue)), font, 15);
        label.setFillColor(sf::Color::White);
        label.setPosition(10, height - 50 - i * (height - 100) / 10 - 10);
        window.draw(label);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Hello world");

    // Load font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }

    std::vector<sf::Vector2f> dataPoints = {
        {19990105.f,6152.43},
        {19990106.f,6199.91},
        {19990107.f,6404.31},
        {19990108.f,6421.75},
        {19990111.f,6406.99},
        {19990112.f,6363.89}
    };

    sf::VertexArray polyline = createPolyline(dataPoints, 1920, 1080);

    sf::VertexArray axes = createAxes(1920, 1080);

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();



        window.draw(polyline);
        window.draw(axes);

        createLabels(window, 1920, 1080, font, dataPoints);

        window.display();
    }

    return 0;
}
