#include "../include/grid.hpp"

#include <algorithm>
#include <cmath>

namespace Algorithms {
    using Constants::GAP_PX;
    using Constants::ZOOM_LOWER_BOUND;
    using Constants::ZOOM_UPPER_BOUND;
    using Constants::ZOOM;

    Grid::Grid() {
        // At the start we do not have any start cell, nor the end cell.
        this->start_cell = this->end_cell = CellPoint(-1, -1);

        // Assume that we didn't scale the world map, and that we didn't offset it at the start.
        this->scale = { 1.0f, 1.0f };
        this->offset = { 0.0f, 0.0f };
    }

    void Grid::SetCellSize(int cell_size) {
        this->cell_size = cell_size;
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

    static bool in_bounds(Vector2 pos, Vector2 top_left, Vector2 bottom_right) {
        return (pos.x >= top_left.x && pos.x <= bottom_right.x && pos.y >= top_left.y && pos.y <= bottom_right.y);
    }

    float Grid::GetGridSize() const {
        return (float) (GRID_SIZE * this->cell_size);
    }

    void Grid::Draw() {
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                // Turn the world position of cell into the screen domain, include the grid gap in the calculation, as we want gap between the cells.
                Vector2 cell_pos = WorldToScreen({ (float)(j * this->cell_size + GAP_PX) , (float) (i * this->cell_size + GAP_PX) });

                if (in_bounds(cell_pos, { -this->cell_size * scale.x, -this->cell_size * scale.y }, { (float) GetRenderWidth(), (float) GetRenderHeight() })) {
                    // Draw the cell, only if its world position in the screen domain is in the bounds of the window that we are drawing on.
                    // We are checking pos.x >= -cell_size * scale.x and same for pos.y, because if pos.x = -cell_size * scale.x + n, that means we would see n pixel(s) of this cell.
                    // Also take into account the gap size when drawing the cell of the size cell width, as we want to have gap around all sides of the cell, not just the top left corner.
                    DrawRectangleV(cell_pos, { (this->cell_size - GAP_PX) * this->scale.x, (this->cell_size - GAP_PX) * this->scale.y }, matrix[i][j].GetFillColor());
                }
            }
        }
    }

    void Grid::ResetZoomAndPan() {
        // Reset the scale to 1.0 for both x and y.
        this->scale = { 1.0f, 1.0f };

        // Take half of A and take half of B subtract them, and you will get the center. Based on that we will set the offset at the center of the screen.
        this->offset = { GetGridSize() / 2 -GetRenderWidth() / 2, GetGridSize() / 2 -GetRenderHeight() / 2 };
    }
    void Grid::MouseSetStartOrEndCell() {
        if ((IsKeyDown(KEY_S) || IsKeyDown(KEY_E)) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 curr_wld = ScreenToWorld({ (float) GetMouseX(), (float) GetMouseY() });

            if (in_bounds(curr_wld, { 0.0f, 0.0f }, { GetGridSize(), GetGridSize() })) {
                // In case the mouse position in the world space is inside of the grid, then take it and map it to the cell of the grid.
                int new_i = curr_wld.y / this->cell_size;
                int new_j = curr_wld.x / this->cell_size;

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
    }

    void Grid::MouseSetWallsOrEmptyCells() {
        if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_N)) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            // If the user is holding W, we will place walls on the empty cells, otherwise we will place empty cells on the wall cells.
            Cell::CellType place_type = IsKeyDown(KEY_W) ? Cell::CellType::WALL : Cell::CellType::EMPTY;
            Cell::CellType on_the_type = (place_type == Cell::CellType::WALL) ? Cell::CellType::EMPTY : Cell::CellType::WALL;

            // Remember the previous mouse position as well as the current one. We want to fill all the cells in between these two positions in the world domain, so that we get the continuous line.
            // At one frame (one iteration of the game loop), the mouse could be at (0, 0), and on another at the (100, 100), due to the target FPS, and that is why we are doing this. Convert it directly to the world domain.
            this->mouse_prev = mouse_curr;
            this->mouse_curr = ScreenToWorld({ (float) GetMouseX(), (float) GetMouseY() });

            if (this->mouse_prev.x == -1 && this->mouse_prev.y == -1) {
                // In case we do not have the previous mouse point, let it be equal to the current mouse point, that way it would seem as if we just made a click for start.
                this->mouse_prev = mouse_curr;
            }

            Vector2 top_left = { 0.0f, 0.0f }, bottom_right = { GetGridSize(), GetGridSize() };
            if (in_bounds(mouse_curr, top_left, bottom_right) && in_bounds(mouse_prev, top_left, bottom_right)) {
                // In case the world space cursor positions are in the grid in the world, then calculate the slope of the line between the current and previous mouse points.
                float x_distance = mouse_curr.x - mouse_prev.x;
                float y_distance = mouse_curr.y - mouse_prev.y;
                float slope = y_distance / x_distance;

                if (std::isnan(slope)) {
                    // If the slope is NaN, that means we divided zero with zero, the previous and the current mouse positions are equal. So we will place only one wall / empty cell.
                    int new_i = mouse_curr.y / cell_size, new_j = mouse_curr.x / cell_size;
                    if (matrix[new_i][new_j].GetType() == on_the_type) {
                        matrix[new_i][new_j].SetType(place_type);
                    }
                }
                else if (abs(x_distance) > abs(y_distance)) {
                    int x_min = std::min(mouse_prev.x, mouse_curr.x);
                    int x_max = std::max(mouse_prev.x, mouse_curr.x);

                    // If the slope is in the range [-1, 1], we will use the y = slope * (x - x0) + y0, to find the y, and we will fill all the cells in between current and previous mouse postion.
                    for (int x = x_min; x <= x_max; ++x) {
                        int y = slope * (x - mouse_prev.x) + mouse_prev.y;
                        int new_i = y / cell_size, new_j = x / cell_size;
                        if (matrix[new_i][new_j].GetType() == on_the_type) {
                            matrix[new_i][new_j].SetType(place_type);
                        }
                    }
                }
                else {
                    int y_min = std::min(mouse_prev.y, mouse_curr.y);
                    int y_max = std::max(mouse_prev.y, mouse_curr.y);

                    // If the slope is not in the range [-1, 1], we will use x = (y - y0) / slope + x0, to find the x, and we will fill all the cells in between the current and previous mouse position.
                    for (int y = y_min; y <= y_max; ++y) {
                        int x = (y - mouse_prev.y) / slope + mouse_prev.x;
                        int new_i = y / cell_size, new_j = x / cell_size;
                        if (matrix[new_i][new_j].GetType() == on_the_type) {
                            matrix[new_i][new_j].SetType(place_type);
                        }
                    }
                 }
            }
        }
        else {
            // If the user didn't do anything, reset the previous and current mouse points.
            this->mouse_prev = this->mouse_curr = { -1, -1 };
        }
    }

    Vector2 Grid::ScreenToWorld(Vector2 scr) {
        // We got this equation from the one below by moving around things around = operator in math.
        return { scr.x / scale.x + offset.x , scr.y / scale.y + offset.y };
    }

    Vector2 Grid::WorldToScreen(Vector2 wld) {
        // scr = (wld - offset) * scale (offset > 0, we move to the right, and things we see to the left, offset < 0, we move to the left, and things we see to the right).
        return { (wld.x - offset.x) * scale.x, (wld.y - offset.y) * scale.y };
    }

    void Grid::MouseZoomAndPan() {
        Vector2 drag = { (float) GetMouseX(), (float) GetMouseY() };

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))) {
            // Set the starting point from where we drag.
            this->start_pan = drag;
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))) {
            // Calculate the distance between the starting point of when we pressed the mouse, and where we dragged the mouse, also apply the scaling on the distance, as we have zoom as well.
            // If the distance is positive, that means we want to drag the things we see to the right, and therefore we want to move to the left (offset < 0)
            // If the distance is negative, that means we want to drag things we see to the left, and therefore we want to move to the right (offset > 0).
            this->offset.x -= (drag.x - this->start_pan.x) / this->scale.x;
            this->offset.y -= (drag.y - this->start_pan.y) / this->scale.y;

            // Reset the starting point after applying the equations above, otherwise we will alter the offset indefinitely.
            this->start_pan = drag;
        }

        // Get the mouse position in the world domain, before zooming anything.
        Vector2 mouse_before_zoom = ScreenToWorld(drag);

        float scroll = GetMouseWheelMove();
        if (scroll >= 0.5f && (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))) {
            // If we are scrolling in the positive direction, increase the scale.
            Vector2 old_scale = scale;
            scale = { scale.x * (1.0f + ZOOM), scale.y * (1.0f + ZOOM) };

            if (scale.x >= ZOOM_UPPER_BOUND || scale.y >= ZOOM_UPPER_BOUND) {
                // If we have reached the upper bound, set the scale to be the previous one before changing it.
                scale = old_scale;
            }
        }
        else if (scroll <= -0.5f && (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))) {
            // If we are scrolling in the negative direction, decrease the scale.
            Vector2 old_scale = scale;
            scale = { scale.x * (1.0f - ZOOM), scale.y * (1.0f - ZOOM) };

            if (scale.x <= ZOOM_LOWER_BOUND || scale.y <= ZOOM_LOWER_BOUND) {
                // If we have reached the lower bound, set the scale to be the previous one before changing it.
                scale = old_scale;
            }
        }

        // Get the mouse position in the world domain, after zooming things.
        Vector2 mouse_after_zoom = ScreenToWorld(drag);

        // If we increased our scale, the distance between the points became greater, as things became larger, therefore no_zoom(x, y) < zoom(x, y), offset has increased.
        // In order to keep the point around which we want to zoom the world, we need to take the difference between zoom(x, y) and no_zoom(x, y), and decrease the offset back by that.
        // If we decreased our scale, the distance became shorter, no_zoom(x, y) > unzoom(x, y), offset decreased, we need to increase it by the difference (that is now negative).
        this->offset.x -= (mouse_after_zoom.x - mouse_before_zoom.x);
        this->offset.y -= (mouse_after_zoom.y - mouse_before_zoom.y);
    }
}
