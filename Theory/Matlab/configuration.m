% Clean
% -----

clear ;
close all ;
clc ;

% Glossary
% --------

% Prefix used:
% d_ : distance
% a_ : angle
% t_ : time
% f_ : frequency
% N_ : decimal number (count - no unit)

% Suffix is linked to object, target etc:
% _tx : Laser Emitter turret (on our main robot)
% _rx : Laser Receiver beacon (on opponent robots and fixed beacon)

% Define configuration
% ---------------------

% Playground configuration
field_width  = 3000 ;
field_height = 2000 ;

% Arbitrary references and startup configuration
beacon_a = [0 0] ;                       % Bottom left beacon
beacon_b = [field_width field_height/2]; % Middle right beacon
beacon_c = [0 field_height];             % Top left beacon

% Distances between beacons
d_ab = norm(beacon_b - beacon_a , 2);
d_bc = norm(beacon_c - beacon_b , 2);
d_ca = norm(beacon_a - beacon_c , 2);

% Angles between beacons
a_ab = atan2((beacon_b(2)-beacon_a(2)),(beacon_b(1)-beacon_a(1)))*180/pi ;
a_bc = atan2((beacon_c(2)-beacon_b(2)),(beacon_c(1)-beacon_b(1)))*180/pi ; 
a_ca = atan2((beacon_c(2)-beacon_a(2)),(beacon_c(1)-beacon_a(1)))*180/pi ;

% Mechanical configuration and constraints
d_la = 40 ;  % (mm) Distance between lasers
d_ph = 10 ;  % (mm) Distance between photodiodes
f_tu = 30 ;  % (Hz) Turret's angular speed

% Hardware configuration
f_cy_rx = 32 ; % (MHz) Fcy frequency on RX-beacon

% Software configuration
lut_min_rx   =  150 ; % (mm) Minimum value in distance contained in the LUT
lut_step_rx  =   16 ; % (mm) Distance step between 2 lut value
lut_depth_rx =  256 ; %  LUT size (number of distance pre-computed values)
distance_lut_c_path = '../../../../Info/2013/beacon_brx/src';
distance_lut_c_filename = 'distance_lut.c' ; % C-file containing LUT filename
distance_lut_h_filename = 'distance_lut.h' ; % C-file header filename

lut_max_rx = lut_min_rx + lut_depth_rx*lut_step_rx ;

% Print configuration
% -------------------

str = sprintf('Configuration used\n------------------\n'); disp(str);
str = sprintf('Distance between laser = %d mm', d_la); disp(str);
str = sprintf('Distance between photodiodes = %d mm', d_ph); disp(str);
str = sprintf('Turret angular speed = %d rps', f_tu); disp(str);
str = sprintf('LUT step = %d mm', lut_step_rx); disp(str);
str = sprintf('LUT depth = %d words', lut_depth_rx); disp(str);
str = sprintf('Minimum distance = %d mm', lut_min_rx); disp(str);
str = sprintf('Reachable distance = %d mm', lut_max_rx ); disp(str);
               

