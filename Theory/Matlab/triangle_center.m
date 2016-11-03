function [center] = triangle_center (points)

    center = (points(1,:) + points(2,:) + points(3,:)) ./ 3 ;
    
end