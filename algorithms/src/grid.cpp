#include "../include/grid.hpp"

#include <iostream>
#include <algorithm>
#include <cmath>

namespace Algorithms {
    using Constants::MARGIN_PX;

    Grid::Grid() {
        // At start we do not have any start and end cells.
        this->start_cell = CellPoint(-1, -1);
        this->end_cell = CellPoint(-1, -1);

        // At the start won't offset the world screen.
        this->offset = { 0.0f, 0.0f };

        // At the start, our world will have scale of 1.0.
        this->scale = { 1.0f, 1.0f };
    }

    void Grid::SetCellSize(int cell_width, int cell_height) {
        this->cell_width = std::max(cell_width, cell_height);
        this->cell_height = this->cell_width;
    }

    void Grid::SetWindowSize(int window_width, int window_height) {
        this->window_width = window_width;
        this->window_height = window_height;
    }

    CellPoint Grid::GetStartCellPoint() const {
        return this->start_cell;
    }

    CellPoint Grid::GetEndCellPoint() const {
        return this->end_cell;
    }

    Cell& Grid::GetCell(int i, int j) {
        return this->matrix[i][j];
    }

    void Grid::Draw() {
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                Vector2 pos = WldToScr({ (float)j * this->cell_width + MARGIN_PX, (float)i * this->cell_height + MARGIN_PX });
                // Draw the matrix of cells with margins between the cells.
                DrawRectangle(pos.x, pos.y, (this->cell_width - MARGIN_PX) * scale.x, (this->cell_height - MARGIN_PX) * scale.y, matrix[i][j].GetFillColor());
            }
        }
    }

    void Grid::HandleMouseEvents() {
        this->MousePickStartOrEndCell();
        this->MouseDrawWallOrEmptyCells();
    }

    void Grid::MousePickStartOrEndCell() {
        if ((IsKeyDown(KEY_S) || IsKeyDown(KEY_E)) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 curr = { (float) GetMouseX(), (float) GetMouseY() };
            curr = ScrToWld(curr);

            // Map the mouse position to the cell of the matrix.
            int new_i = curr.y / cell_height;
            int new_j = curr.x / cell_width;

            if (matrix[new_i][new_j].GetType() == Cell::CellType::EMPTY) {
                // If the user is holding S, the cell that we will work with is start, otherwise he is holding E and then we will work with the end cell.
                Cell::CellType type = IsKeyDown(KEY_S) ? Cell::CellType::START : Cell::CellType::END;
                CellPoint& ref_cell = IsKeyDown(KEY_S) ? start_cell : end_cell;

                if (ref_cell.IsValid()) {
                    // In case we set the start or the end cell in the past remove it. We want to have only one start and the end cell.
                    matrix[ref_cell.I()][ref_cell.J()].SetType(Cell::CellType::EMPTY);
                }

                // Remember the new position of the cell, and set its type in the matrix.
                ref_cell = CellPoint(new_i, new_j);
                matrix[new_i][new_j].SetType(type);
            }
        }
    }

    static bool in_bounds(Vector2 pos, int x_min, int x_max, int y_min, int y_max) {
        // Check if vector is in the proper bounds. This will be used to check if the mouse position is in the bounds of the window.
        return (pos.x >= x_min && pos.x <= x_max && pos.y >= y_min && pos.y <= y_max);
    }

    void Grid::MouseDrawWallOrEmptyCells() {
        if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_N)) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            // If the user is holding W, we will place walls on the empty cells, otherwise we will place empty cells on the wall cells.
            Cell::CellType place_type = IsKeyDown(KEY_W) ? Cell::CellType::WALL : Cell::CellType::EMPTY;
            Cell::CellType on_the_type = (place_type == Cell::CellType::WALL) ? Cell::CellType::EMPTY : Cell::CellType::WALL;

            // Remember the previous mouse position as well as the current one. We want to fill all the cells in between these two positions, so that we get the continuous line.
            // At one frame (one iteration of the game loop), the mouse could be at (0, 0), and on another at the (100, 100), due to the target FPS.
            this->mouse_prev = mouse_curr;
            this->mouse_curr = { (float) GetMouseX(), (float) GetMouseY() };

            this->mouse_prev_wld = mouse_curr_wld;
            this->mouse_curr_wld = ScrToWld(mouse_curr);
            if (this->mouse_prev_wld.x == -1 && this->mouse_prev_wld.y == -1) {
                this->mouse_prev_wld = mouse_curr_wld;
            }

            Vector2 top_left = ScrToWld({ 0, 0 });
            Vector2 bottom_right = ScrToWld({ (float)window_width, (float)window_height });

            if (in_bounds(mouse_curr_wld, top_left.x, bottom_right.x, top_left.y, bottom_right.y) && in_bounds(mouse_prev_wld, top_left.x, bottom_right.x, top_left.y, bottom_right.y)) {
                // Calculate the slope of the line between the previous and current mouse position.
                float x_distance = mouse_curr_wld.x - mouse_prev_wld.x;
                float y_distance = mouse_curr_wld.y - mouse_prev_wld.y;
                float slope = y_distance / x_distance;

                if (std::isnan(slope)) {
                    // If the slope is NaN, that means we divided zero with zero, the previous and the current mouse positions are equal. So we will place only one wall / empty cell.
                    int new_i = mouse_curr_wld.y / cell_height, new_j = mouse_curr_wld.x / cell_width;
                    if (matrix[new_i][new_j].GetType() == on_the_type) {
                        matrix[new_i][new_j].SetType(place_type);
                    }
                }
                else if (abs(x_distance) > abs(y_distance)) {
                    int x_min = std::min(mouse_prev_wld.x, mouse_curr_wld.x); 
                    int x_max = std::max(mouse_prev_wld.x, mouse_curr_wld.x);

                    // If the slope is in the range [-1, 1], we will use the y = slope * (x - x0) + y0, to find the y, and we will fill all the cells in between current and previous mouse postion.
                    for (int x = x_min; x <= x_max; ++x) {
                        int y = slope * (x - mouse_prev_wld.x) + mouse_prev_wld.y;
                        int new_i = y / cell_height, new_j = x / cell_width;
                        if (matrix[new_i][new_j].GetType() == on_the_type) {
                            matrix[new_i][new_j].SetType(place_type);
                        }
                    }
                }
                else {
                    int y_min = std::min(mouse_prev_wld.y, mouse_curr_wld.y);
                    int y_max = std::max(mouse_prev_wld.y, mouse_curr_wld.y);

                    // If the slope is not in the range [-1, 1], we will use x = (y - y0) / slope + x0, to find the x, and we will fill all the cells in between the current and previous mouse position.
                    for (int y = y_min; y <= y_max; ++y) {
                        int x = (y - mouse_prev_wld.y) / slope + mouse_prev_wld.x;
                        int new_i = y / cell_height, new_j = x / cell_width;
                        if (matrix[new_i][new_j].GetType() == on_the_type) {
                            matrix[new_i][new_j].SetType(place_type);
                        }
                    }
                 }
            }
        }
        else {
            // If the user didn't do anything, reset the previous and current mouse positions.
            this->mouse_prev = { -1, -1 };
            this->mouse_curr = { -1, -1 };
            this->mouse_prev_wld = { -1, -1 };
            this->mouse_curr_wld = { -1, -1 };
        }
    }

    Vector2 Grid::ScrToWld(Vector2 scr) {
        return { scr.x / scale.x + offset.x , scr.y / scale.y + offset.y };
    }

    Vector2 Grid::WldToScr(Vector2 wld) {
        return { (wld.x - offset.x) * scale.x, (wld.y - offset.y) * scale.y };
    }

    void Grid::MouseZoomPan() {
        static Vector2 s_of;
        Vector2 mcur = { (float) GetMouseX(), (float) GetMouseY() };

        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            s_of = mcur;
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            offset.x -= (mcur.x - s_of.x) / scale.x;
            offset.y -= (mcur.y - s_of.y) / scale.y;
            s_of = mcur;
        }

        Vector2 mouseBeforeZoom = ScrToWld(mcur);

        float scroll = GetMouseWheelMove();
        if (scroll >= 0.5) {
            scale = { scale.x * 1.1f, scale.y * 1.1f };
        }
        else if (scroll <= -0.5) {
            scale = { scale.x * .9f, scale.y * .9f };
        }

        Vector2 mouseAfterZoom = ScrToWld(mcur);

        offset.x -= (mouseAfterZoom.x - mouseBeforeZoom.x);
        offset.y -= (mouseAfterZoom.y - mouseBeforeZoom.y);
    }
}

