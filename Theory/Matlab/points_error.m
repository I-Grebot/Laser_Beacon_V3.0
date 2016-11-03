function [error] = points_error(w, h, m, p1, p2, p3)
    
    if((p1(1) < -m  && p2(1) < -m  && p3(1) < -m) || ...
       (p1(1) > w+m && p1(1) > w+m && p3(1) > w)  || ...
       (p1(2) < -m  && p1(2) < -m  && p3(2) < -m) || ...
       (p1(2) > h+m && p1(2) > h+m && p3(2) > h+m))
        error = inf;
    else
        error = norm(p1 - p2) + norm(p2 - p3) + norm(p3 - p1) ;
    end
end