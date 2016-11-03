function [inter1, inter2] = circles_intersect(r1, c1, r2, c2)

% Compute distance between circles
d_12 = norm(c2-c1);

% Unit vector from first to second center
u_12 = (c2 - c1)/d_12;

% Perpendicular vector to unit vector
pu_12 = [u_12(2), -u_12(1)];

% Use the cosine of alpha to calculate the length of the
% vector along and perpendicular to [C1C2] that leads to the
% intersection point
cosAlpha = (r1^2+d_12^2-r2^2)/(2*r1*d_12);

inter1 = c1 + u_12 * (r1*cosAlpha) + pu_12 * (r1*sqrt(1-cosAlpha^2));
inter2 = c1 + u_12 * (r1*cosAlpha) - pu_12 * (r1*sqrt(1-cosAlpha^2));


end