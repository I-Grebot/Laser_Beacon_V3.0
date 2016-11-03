%%
% CONFIGURATION
% -------------

% Run startup calls and configuration
configuration

% Maximum limit for 3D display
max_limit = 50;

%%
% TEST CONFIGURATION
% ------------------

% Single value on/off
single_value = 0 ;
single_robot = [2900 1900];

% Number of beacon used
% 3: Automatically use the 2 best beacons
% 2: Use the 2 specified beacons
% 1: Use the specify beacon
nb_beacon = 1 ;

% Computation method
method = 3;

% Beacon configuration for dual/single mode
% 'AB', 'BC', 'CA' for dual config
% 'A', 'B' or 'C' for single config
beacon_config = 'AB' ;
    
% Measurements errors
mes_a_err = 0.5     ; % In degree
mes_d_err = 1.0/100 ; % In percent

% Loop's steps (mm)
step_x = 10 ;
step_y = 10 ;

% Margin for edges
edge_margin = 120 ;

% Tolerance for edges
tolerance = -120;

if(single_value == 1)
    vect_x = 1;
    vect_y = 1;   
else  
    % Allocate memory for error array
    error = zeros(floor((field_width-2*edge_margin)/step_x), floor((field_height-2*edge_margin)/step_y));

    % Loop on robot position (avoid corners)
    vect_x = 1:(field_width-2*edge_margin)/step_x;
    vect_y = 1:(field_height-2*edge_margin)/step_y;
end

for idx_x = vect_x
    for idx_y = vect_y
        
    % Place the robot at a given position an infer measured values
    if(single_value == 1)
        robot = single_robot;
    else        
        robot = [idx_x*step_x+edge_margin idx_y*step_y+edge_margin] ;
    end        

    % Compute measured distances to beacons in mm
    mes_d_a = norm(beacon_a - robot)*(1+mes_d_err);
    mes_d_b = norm(beacon_b - robot)*(1+mes_d_err);
    mes_d_c = norm(beacon_c - robot)*(1+mes_d_err);

    % Compute measured angles to beacons
    mes_a_ra = atan2((beacon_a(2)-robot(2)),(beacon_a(1)-robot(1)))*180/pi ; % Between -180° and -90°
    mes_a_rb = atan2((beacon_b(2)-robot(2)),(beacon_b(1)-robot(1)))*180/pi ; % Between -90° and +90°
    mes_a_rc = atan2((beacon_c(2)-robot(2)),(beacon_c(1)-robot(1)))*180/pi ; % Between -180° and -90°

    % Measured angles between beacons
    mes_a_ab = (mes_a_rb - mes_a_ra)+mes_a_err;
    mes_a_bc = (mes_a_rc - mes_a_rb)+mes_a_err; 
    mes_a_ca = (mes_a_ra - mes_a_rc)+mes_a_err;
    
    mes_a_a = mes_a_ra+mes_a_err;
    mes_a_b = mes_a_rb+mes_a_err;
    mes_a_c = mes_a_rc+mes_a_err;

    %%
    % ALGORITHM
    % ---------
    
    % Determine the 2 beacons which will be used for measurement
    % (Now denoted as '1' and '2')
    
    beacon_a_closest = mes_d_a <= mes_d_b && mes_d_a <= mes_d_c ;
    beacon_b_closest = mes_d_b <= mes_d_a && mes_d_b <= mes_d_c ;
    beacon_c_closest = mes_d_c <= mes_d_a && mes_d_c <= mes_d_b ; 
    beacon_a_farest  = mes_d_a >= mes_d_b && mes_d_a >= mes_d_c ;
    beacon_b_farest  = mes_d_b >= mes_d_a && mes_d_b >= mes_d_c ;
    beacon_c_farest  = mes_d_c >= mes_d_a && mes_d_c >= mes_d_b ;

    % Use AB if C is the closest or A is the farest
    % Use BC if A is the closest or C is the farest
    % Do not use CA
    if(method == 1)
        use_beacon_ab = (beacon_c_closest || beacon_a_farest) ;
        use_beacon_bc = (beacon_a_closest || beacon_c_farest) ;
        use_beacon_ca = 0 ;
        
    % 2nd method : all beacons have similar error
    elseif(method == 2)
        use_beacon_ab = (beacon_c_closest || beacon_a_farest) ;
        use_beacon_bc = (beacon_a_closest || beacon_c_farest) ;
        use_beacon_ca = beacon_b_farest ;
    
    % 3rd method
    elseif(method == 3)
        use_beacon_ab = (beacon_c_closest || beacon_a_farest) ;
        use_beacon_bc = (beacon_a_closest || beacon_c_farest) ;
        use_beacon_ca = beacon_b_farest ;        
    end
        
    % Measurements with C and A
    if((nb_beacon == 3 && use_beacon_ca) || ...
           (nb_beacon == 2 && strcmp(beacon_config,'CA')))   
        mes_a_12 = mes_a_ca ;
        a_12     = a_ca     ;
        d_12     = d_ca     ;
        mes_d_1  = mes_d_c  ;
        beacon_1 = beacon_c ;
        mes_d_2  = mes_d_a  ;
        beacon_2 = beacon_a ; 
        mes_a_1 = mes_a_c   ;
        mes_a_2 = mes_a_a   ;
    
    % Measurements with B and C
    elseif((nb_beacon == 3 && use_beacon_bc) || ...
           (nb_beacon == 2 && strcmp(beacon_config,'BC')))      
        mes_a_12 = mes_a_bc ;
        a_12     = a_bc     ;
        d_12     = d_bc     ;
        mes_d_1  = mes_d_b  ;
        beacon_1 = beacon_b ;
        mes_d_2  = mes_d_c  ;
        beacon_2 = beacon_c ;
        mes_a_1 = mes_a_b   ;
        mes_a_2 = mes_a_c   ;
        
    % Measurements with A and B
    elseif((nb_beacon == 3 && use_beacon_ab) || ...
       (nb_beacon == 2 && strcmp(beacon_config,'AB')))
        mes_a_12 = mes_a_ab ;
        a_12     = a_ab     ;
        d_12     = d_ab     ;
        mes_d_1  = mes_d_a  ;
        beacon_1 = beacon_a ;
        mes_d_2  = mes_d_b  ;
        beacon_2 = beacon_b ;
        mes_a_1 = mes_a_a   ;
        mes_a_2 = mes_a_b   ;

    % Measurement with a single beacon
    elseif(nb_beacon == 1 && strcmp(beacon_config,'A'))        
        mes_a_1 = mes_a_a   ;
        mes_d_1 = mes_d_a   ;
        beacon_1 = beacon_a ;
    elseif(nb_beacon == 1 && strcmp(beacon_config,'B'))        
        mes_a_1 = mes_a_b   ;
        mes_d_1 = mes_d_b   ;
        beacon_1 = beacon_b ;
    else        
        mes_a_1 = mes_a_c   ;
        mes_d_1 = mes_d_c   ;
        beacon_1 = beacon_c ;        
    end

    % Algorithm used when 2 beacons are available
    if(nb_beacon >= 2)

        if(method == 1)
            
            % -----------------------------------------------
            % Determine C1:
            % Circle going through the 2 beacons + the robot
            rc1_angle = mes_a_12 ;
            if(rc1_angle > 180)
                rc1_angle = rc1_angle-180;
            elseif(rc1_angle < -180)
                rc1_angle = rc1_angle+180;
            end

            rc1   = abs(d_12 / (2*sind(rc1_angle)))          ; % Radius 
            c1(1) = beacon_1(1) + rc1*sind(rc1_angle - a_12) ; % Center
            c1(2) = beacon_1(2) + rc1*cosd(rc1_angle - a_12) ;

            % -----------------------------------------------
            % Determine C2:
            % Circle centered in beacon A and crossing the robot
            rc2 = mes_d_1     ; % Radius
            c2  = beacon_1    ; % Center

            % -----------------------------------------------
            % Determine C3:
            % Circle centered in beacon B and crossing the robot
            rc3 = mes_d_2     ; % Radius
            c3  = beacon_2    ; % Center

            % -----------------------------------------------
            % The 3 circles intersect in (xr;yr), robot's position
            [inter_121 inter_122] = circles_intersect(rc1, c1, rc2, c2);
            [inter_231 inter_232] = circles_intersect(rc2, c2, rc3, c3);
            [inter_311 inter_312] = circles_intersect(rc3, c3, rc1, c1);
            inter = [inter_121; inter_122; inter_231; inter_232; inter_311; inter_312];

            % -----------------------------------------------
            % Find the common intercection between the 3 circles          

            points_errors(1) = points_error(field_width, field_height, tolerance, inter(1,:), inter(3,:), inter(5,:));
            points_errors(2) = points_error(field_width, field_height, tolerance, inter(1,:), inter(3,:), inter(6,:));
            points_errors(3) = points_error(field_width, field_height, tolerance, inter(1,:), inter(4,:), inter(5,:));
            points_errors(4) = points_error(field_width, field_height, tolerance, inter(1,:), inter(4,:), inter(6,:));
            points_errors(5) = points_error(field_width, field_height, tolerance, inter(2,:), inter(3,:), inter(5,:));
            points_errors(6) = points_error(field_width, field_height, tolerance, inter(2,:), inter(3,:), inter(6,:));
            points_errors(7) = points_error(field_width, field_height, tolerance, inter(2,:), inter(4,:), inter(5,:));
            points_errors(8) = points_error(field_width, field_height, tolerance, inter(2,:), inter(4,:), inter(6,:));    

            [point_error min_error_idx] = min(points_errors);

            if(min_error_idx == 1)
                triangle_points = [inter(1,:); inter(3,:); inter(5,:)];

            elseif(min_error_idx == 2)
                triangle_points = [inter(1,:); inter(3,:); inter(6,:)];

            elseif(min_error_idx == 3)
                triangle_points = [inter(1,:); inter(4,:); inter(5,:)];

            elseif(min_error_idx == 4)
                triangle_points = [inter(1,:); inter(4,:); inter(6,:)];

            elseif(min_error_idx == 5)
                triangle_points = [inter(2,:); inter(3,:); inter(5,:)];

            elseif(min_error_idx == 6)
                triangle_points = [inter(2,:); inter(3,:); inter(6,:)];

            elseif(min_error_idx == 7)
                triangle_points = [inter(2,:); inter(4,:); inter(5,:)];

            elseif(min_error_idx == 8)
                triangle_points = [inter(2,:); inter(4,:); inter(6,:)];
            end          

            computed_robot = triangle_center(triangle_points);
        
        % ---------------------------------------------
        elseif(method >= 2)
            
            % ------------------------------------------------
            % Compute C1
            
            rc1 = mes_d_1     ; % Radius
            c1  = beacon_1    ; % Center

            % The only solution is the crossing of the circle
            % and the measured angle
            linear_points(1,1) = c1(1) - rc1 * cosd(mes_a_1) ;
            linear_points(1,2) = c1(2) - rc1 * sind(mes_a_1) ;
            
            % ------------------------------------------------
            % Compute C2
            
            rc2 = mes_d_2     ; % Radius
            c2  = beacon_2    ; % Center

            % The only solution is the crossing of the circle
            % and the measured angle
            linear_points(2,1) = c2(1) - rc2 * cosd(mes_a_2) ;
            linear_points(2,2) = c2(2) - rc2 * sind(mes_a_2) ;
            
            if(method == 3)
                % Compute the intersection of the 2 circles
                [inter_121 inter_122] = circles_intersect(rc1, c1, rc2, c2);

                inter = [inter_121; inter_122];

                % Check wether 121 or 122 is the good intersection point
                points_errors(1) = points_error(field_width, field_height, tolerance, inter(1,:), linear_points(1,:), linear_points(2,:));
                points_errors(2) = points_error(field_width, field_height, tolerance, inter(2,:), linear_points(1,:), linear_points(2,:));

                [point_error min_error_idx] = min(points_errors);

                if(min_error_idx == 1)
                    triangle_points = [linear_points(1,:); linear_points(2,:); inter(1,:)];
                else
                    triangle_points = [linear_points(1,:); linear_points(2,:); inter(2,:)];
                end
                
                % Computed position is at half distance
                computed_robot = triangle_center(triangle_points);
            
            else                            
                computed_robot = (linear_points(1,:) + linear_points(2,:))./2 ;
            end
            
        end
        
    % Algorithm used if only 1 beacon is used
    else

        rc1 = mes_d_1     ; % Radius
        c1  = beacon_1    ; % Center

        % The only solution is the crossing of the circle
        % and the measured angle
        computed_robot(1) = c1(1) - rc1 * cosd(mes_a_1) ;
        computed_robot(2) = c1(2) - rc1 * sind(mes_a_1) ;


    end

    % -----------------------------------------------
    % COMPUTE ERROR

%     norm(computed_robot - robot)
    error(idx_x, idx_y) = norm(computed_robot - robot); % in mm

    
    end % Y-step
end % X-step

error_max = max(max(error)) ;
error_min = min(min(error)) ;
error_mean = mean(mean(error)) ;
error_std = mean(std(error)) ;

% -----------------------------------------------
% PLOTs

figure;

% Error plot
if(single_value == 1)

    % Draw the field
    plot([0 0 field_width field_width, 0], [0, field_height, field_height, 0, 0], '--r', 'LineWidth',2);
    hold on

    % Place beacons
    plot([beacon_a(1) beacon_b(1) beacon_c(1)],[beacon_a(2) beacon_b(2) beacon_c(2)], ...
         's', 'MarkerEdgeColor','k', 'MarkerFaceColor', 'g', 'MarkerSize', 5)

    % Place C1 center
    %plot([c1(1)],[c1(2)], ...
    %     's', 'MarkerEdgeColor','k', 'MarkerFaceColor','b', 'MarkerSize', 5)

    % Plot C1, C2, C3 circles
    a_plots = 0:pi/100:2*pi;
    plot(c1(1) + rc1*cos(a_plots), c1(2) + rc1*sin(a_plots), 'b');
    
    if(nb_beacon >= 2)
        plot(c2(1) + rc2*cos(a_plots), c2(2) + rc2*sin(a_plots), 'b');
        
        if(method == 1)
            plot(c3(1) + rc3*cos(a_plots), c3(2) + rc3*sin(a_plots), 'b');
        end
        
        % Plot computed intersection points
        if(method == 1)
            plot(inter(:,1), inter(:,2), ...
                's', 'MarkerEdgeColor','k', 'MarkerFaceColor', 'b', 'MarkerSize', 5)
        else
            plot(linear_points(:,1), linear_points(:,2), ...
            's', 'MarkerEdgeColor','k', 'MarkerFaceColor', 'b', 'MarkerSize', 5)
        end
    end
    
    % Plot robot found position
    plot(computed_robot(1), computed_robot(2), ...
        's', 'MarkerEdgeColor','k', 'MarkerFaceColor', 'r', 'MarkerSize', 5)

    % Plot actual robot position
    plot(robot(1), robot(2), ...
        's', 'MarkerEdgeColor','k', 'MarkerFaceColor', 'k', 'MarkerSize', 5)

    str = sprintf('Field configuration at (%d;%d) with angle error = %.1f° and distance error = %.1f%%\nMeasured position = (%.1f;%.1f), error = %.1f mm', ...
        robot(1), robot(2), mes_a_err, mes_d_err*100, computed_robot(1), computed_robot(2), error);
    title(str);
    axis([-field_width/10 field_width*1.1 -field_height/10 field_height*1.1]);

else
    str = sprintf('Overall position error with angle error = %.1f° and distance error = %.1f%%\nUsing %d beacons and method %d\nError = [%.0f;%.0f] mm (mean = %.1f)', ...
        mes_a_err, mes_d_err*100, nb_beacon, method, error_min, error_max, error_mean);
    surf(vect_x.*step_x+edge_margin, vect_y.*step_y+edge_margin, error');
    colorbar;
    title(str);
    shading(gca,'interp');
    axis([0 field_width 0 field_height 0 max_limit]); %
    caxis([0 max_limit]);
    
    str = sprintf('\nResults\n------------------\n'); disp(str);
    str = sprintf('Errors: min = %.1f, max = %.1f, mean = %.1f, std = %.1f\n', error_min, error_max, error_mean, error_std); disp(str);
end



