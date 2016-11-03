
%%
% Run startup calls and configuration
configuration

%%
% Compute distance to opponent table
d_op = lut_min_rx:lut_step_rx:lut_min_rx+(lut_depth_rx-1)*lut_step_rx;

% Compute turret's rotation angles between the 2 photodiodes (degree)
a_tu = asin(d_la./d_op) * 180/pi;

% Compute the time between the 2 laser pulses for the given distance (µs)
t_delta_ph = 1e9 * a_tu ./ (f_tu*360);

% Same value but in number of achievable sampling step from RX
N_dph = round(t_delta_ph * f_cy_rx / 1e3);

% Print out header values in the dedicated file
disp(' ');
disp('Generate header (see output .h file)')
disp('------------------------------------');
disp(' ');


lut_h_fid = fopen([distance_lut_c_path, '/', distance_lut_h_filename], 'w');

fprintf(lut_h_fid, '/* -----------------------------------------------------------------------------\n');
fprintf(lut_h_fid, ' * Beacon [BRX]\n');
fprintf(lut_h_fid, ' * I-Grebot Laser Beacon V3.0\n');
fprintf(lut_h_fid, ' * -----------------------------------------------------------------------------\n');
fprintf(lut_h_fid, ' * File        : %s\n', distance_lut_h_filename);
fprintf(lut_h_fid, ' * Language    : C\n');
fprintf(lut_h_fid, ' * Author      : Paul M.\n');
fprintf(lut_h_fid, ' * Creation    : 2013-03-23\n');
fprintf(lut_h_fid, ' * -----------------------------------------------------------------------------\n');
fprintf(lut_h_fid, ' * Description\n');
fprintf(lut_h_fid, ' *   This file was automatically generated the %s.\n', datestr(now));
fprintf(lut_h_fid, ' *   See main module header file for a full description\n');
fprintf(lut_h_fid, ' * -----------------------------------------------------------------------------\n');
fprintf(lut_h_fid, ' * Versionning informations\n');
fprintf(lut_h_fid, ' * Repository: http://svn2.assembla.com/svn/paranoid_android/\n');
fprintf(lut_h_fid, ' * -----------------------------------------------------------------------------\n');
fprintf(lut_h_fid, ' * $Rev::                                                                      $\n');
fprintf(lut_h_fid, ' * $LastChangedBy::                                                            $\n');
fprintf(lut_h_fid, ' * $LastChangedDate::                                                          $\n');
fprintf(lut_h_fid, ' * -----------------------------------------------------------------------------\n');
fprintf(lut_h_fid, ' */\n\n');

fprintf(lut_h_fid, '#ifndef _DISTANCE_LUT_H_\n');
fprintf(lut_h_fid, '#define _DISTANCE_LUT_H_\n\n');

fprintf(lut_h_fid, '// -----------------------------------------------------------------------------\n');
fprintf(lut_h_fid, '// DISTANCES LOOK-UP-TABLE PARAMETERS\n');
fprintf(lut_h_fid, '// -----------------------------------------------------------------------------\n\n');

fprintf(lut_h_fid, '// The LUT and parameters were generated assuming the following conditions:\n');
fprintf(lut_h_fid, '// * Distance between lasers      = %d mm\n', d_la);
fprintf(lut_h_fid, '// * Distance between photodiodes = %d mm\n', d_ph);
fprintf(lut_h_fid, '// * Turret angular speed         = %d rp/s\n', f_tu);
fprintf(lut_h_fid, '// * FCY                          = %d MHz\n\n', f_cy_rx);

fprintf(lut_h_fid, '#if FCY != %d\n', f_cy_rx*1e6);
fprintf(lut_h_fid, '  #error "Expected FCY frequency do not match with value used for LUT generation!"\n');
fprintf(lut_h_fid, '#endif // FCY\n\n');

fprintf(lut_h_fid, '#if DRUM_MOTOR_SPEED_TARGET_RPS != %d\n', f_tu);
fprintf(lut_h_fid, '  #error "Expected Turret frequency do not match with value used for LUT generation!"\n');
fprintf(lut_h_fid, '#endif // DRUM_MOTOR_SPEED_TARGET_RPS\n\n');

fprintf(lut_h_fid, '#define DISTANCE_LUT_DEPTH %d\n', lut_depth_rx);
fprintf(lut_h_fid, '#define DISTANCE_LUT_STEP_MM %d\n\n', lut_step_rx);

fprintf(lut_h_fid, '#define DISTANCE_LUT_MAX_NCY %d // min distance in mm\n', N_dph(1));
fprintf(lut_h_fid, '#define DISTANCE_LUT_MIN_NCY %d // max distance in mm\n\n', N_dph(lut_depth_rx));

fprintf(lut_h_fid, '#define DISTANCE_LUT_MIN_MM %d\n', lut_min_rx);
fprintf(lut_h_fid, '#define DISTANCE_LUT_MAX_MM %d\n\n', lut_max_rx);

fprintf(lut_h_fid, '#endif // !_DISTANCE_LUT_H_\n');

% End of H-file writing
fclose(lut_h_fid);

% Print out LUT values in the dedicated C module file
disp(' ');
disp('Generate LUT values (see output .c file)')
disp('---------------------------------------');
disp(' ');

lut_c_fid = fopen([distance_lut_c_path, '/', distance_lut_c_filename], 'w');

fprintf(lut_c_fid, '/* -----------------------------------------------------------------------------\n');
fprintf(lut_c_fid, ' * Beacon [BRX]\n');
fprintf(lut_c_fid, ' * I-Grebot Laser Beacon V3.0\n');
fprintf(lut_c_fid, ' * -----------------------------------------------------------------------------\n');
fprintf(lut_c_fid, ' * File        : %s\n', distance_lut_c_filename);
fprintf(lut_c_fid, ' * Language    : C\n');
fprintf(lut_c_fid, ' * Author      : Paul M.\n');
fprintf(lut_c_fid, ' * Creation    : 2013-03-23\n');
fprintf(lut_c_fid, ' * -----------------------------------------------------------------------------\n');
fprintf(lut_c_fid, ' * Description\n');
fprintf(lut_c_fid, ' *   This file was automatically generated the %s.\n', datestr(now));
fprintf(lut_c_fid, ' *   See main module header file for a full description\n');
fprintf(lut_c_fid, ' * -----------------------------------------------------------------------------\n');
fprintf(lut_c_fid, ' * Versionning informations\n');
fprintf(lut_c_fid, ' * Repository: http://svn2.assembla.com/svn/paranoid_android/\n');
fprintf(lut_c_fid, ' * -----------------------------------------------------------------------------\n');
fprintf(lut_c_fid, ' * $Rev::                                                                      $\n');
fprintf(lut_c_fid, ' * $LastChangedBy::                                                            $\n');
fprintf(lut_c_fid, ' * $LastChangedDate::                                                          $\n');
fprintf(lut_c_fid, ' * -----------------------------------------------------------------------------\n');
fprintf(lut_c_fid, ' */\n\n');

fprintf(lut_c_fid, '#include "beacon_brx.h"\n\n');

fprintf(lut_c_fid, '// -----------------------------------------------------------------------------\n');
fprintf(lut_c_fid, '// DISTANCES IN NCY UNIT LOOK-UP-TABLE\n');
fprintf(lut_c_fid, '// -----------------------------------------------------------------------------\n\n');

fprintf(lut_c_fid, 'const uint16_t lut_dist_ncy[DISTANCE_LUT_DEPTH] __attribute__((space(psv))) = {\n   ');
for idx = 1:lut_depth_rx
   if (idx > 1) fprintf(lut_c_fid, '  ,'); end   
   fprintf(lut_c_fid, '%5d // [%d] => %d mm\n', N_dph(idx), idx-1, d_op(idx));   
end
fprintf(lut_c_fid, '}; // lut_dist_ncy\n\n');

fprintf(lut_c_fid, 'inline uint16_t distance_lut_get_ncy(uint16_t _lut_idx) {\n');
fprintf(lut_c_fid, '  return lut_dist_ncy[_lut_idx];\n');
fprintf(lut_c_fid, '}\n\n');

fprintf(lut_c_fid, '// -----------------------------------------------------------------------------\n');
fprintf(lut_c_fid, '// DISTANCES IN MM UNIT FROM INDEX\n');
fprintf(lut_c_fid, '// -----------------------------------------------------------------------------\n\n');

fprintf(lut_c_fid, 'inline uint16_t distance_lut_get_mm(uint16_t _idx) {\n');
fprintf(lut_c_fid, '  return DISTANCE_LUT_MIN_MM + DISTANCE_LUT_STEP_MM*_idx;\n');
fprintf(lut_c_fid, '}\n');
fclose(lut_c_fid);

%%

% Error precision computation in cycles
N_error_prec = 500 ;

% Compute error for each cycle value within the sweep
N_dph_test = N_dph(lut_depth_rx-1):N_error_prec:N_dph(1);

d_op_computed = zeros(1,size(N_dph_test,2));

for idx = 1:size(N_dph_test,2)
    
    % Compute the LUT indexes
    lut_idx = find(N_dph <= N_dph_test(idx), 2, 'first');
    
    % Compute the delta between the two consecutive LUT elements
    N_dlut = N_dph(lut_idx(1)) - N_dph(lut_idx(2));
    
    % Compute interpolation correction for each tested value
    d_op_interp = floor(lut_step_rx * (N_dph(lut_idx(1)) - N_dph_test(idx))/N_dlut);
    
    % Final computed distance to opponent for the tested value
    d_op_computed(idx) = d_op(lut_idx(1)) + d_op_interp;
    
end

% Compute real values for the computed d_op
d_op_real = d_la ./ (sin(N_dph_test * f_tu /(2*pi*1e6)));

% Plot computed and real curves
plot(N_dph_test, d_op_computed, 'b', N_dph_test, d_op_real, 'r');
title('Distance to beacon (mm)');
legend('Computed', 'Actual');

% Compute error vector
d_op_error = d_op_computed - d_op_real;

% Plot error
figure;
plot(N_dph_test, abs(d_op_error));
title('Error (mm)');

% Display RMS error statistics
disp(' ');
disp('Error statistics')
disp('----------------');
disp(' ');
idx_1m = find(d_op_real <= 1000, 1, 'first');
idx_2m = find(d_op_real <= 2000, 1, 'first');
str = sprintf('Total RMS error (1m range) = %.2f mm', ...
        rms(d_op_error(idx_1m:size(N_dph_test,2))));
disp(str);
str = sprintf('Total RMS error (2m range) = %.2f mm', ...
        rms(d_op_error(idx_2m:size(N_dph_test,2))));
disp(str);
str = sprintf('Total RMS error (full range) = %.2f mm', ...
        rms(d_op_computed - d_op_real)); disp(str);


