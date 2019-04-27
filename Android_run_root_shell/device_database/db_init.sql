BEGIN TRANSACTION;
DROP TABLE IF EXISTS supported_devices;
DROP TABLE IF EXISTS device_address;
CREATE TABLE supported_devices(device_id INTEGER PRIMARY KEY ASC, device TEXT NOT NULL, build_id TEXT NOT NULL, check_property_name TEXT, check_property_value TEXT, UNIQUE (device, build_id, check_property_name, check_property_value));

CREATE TABLE device_address(device_id INTEGER NOT NULL, name TEXT NOT NULL, value INTEGER NOT NULL, PRIMARY KEY(device_id, name));

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(1, 'C1505', '11.3.A.0.47', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(1, 'prepare_kernel_cred', '0xc00adb98');
  INSERT INTO device_address(device_id, name, value) VALUES(1, 'commit_creds', '0xc00ad80c');
  INSERT INTO device_address(device_id, name, value) VALUES(1, 'remap_pfn_range', '0xc01028d8');
  INSERT INTO device_address(device_id, name, value) VALUES(1, 'ptmx_fops', '0xc093ee30');
  INSERT INTO device_address(device_id, name, value) VALUES(1, 'perf_swevent_enabled', '0xc093762c');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(2, 'C1505', '11.3.A.2.13', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(2, 'prepare_kernel_cred', '0xc00add90');
  INSERT INTO device_address(device_id, name, value) VALUES(2, 'commit_creds', '0xc00ada04');
  INSERT INTO device_address(device_id, name, value) VALUES(2, 'remap_pfn_range', '0xc0102ad0');
  INSERT INTO device_address(device_id, name, value) VALUES(2, 'ptmx_fops', '0xc093ed70');
  INSERT INTO device_address(device_id, name, value) VALUES(2, 'perf_swevent_enabled', '0xc093756c');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(3, 'C5302', '12.0.A.1.284', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(3, 'prepare_kernel_cred', '0xc009ec08');
  INSERT INTO device_address(device_id, name, value) VALUES(3, 'commit_creds', '0xc009e72c');
  INSERT INTO device_address(device_id, name, value) VALUES(3, 'remap_pfn_range', '0xc011445c');
  INSERT INTO device_address(device_id, name, value) VALUES(3, 'ptmx_fops', '0xc0e3bed8');
  INSERT INTO device_address(device_id, name, value) VALUES(3, 'perf_swevent_enabled', '0xc0e219b4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(4, 'C5303', '12.0.A.1.284', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(4, 'prepare_kernel_cred', '0xc009ec08');
  INSERT INTO device_address(device_id, name, value) VALUES(4, 'commit_creds', '0xc009e72c');
  INSERT INTO device_address(device_id, name, value) VALUES(4, 'remap_pfn_range', '0xc011445c');
  INSERT INTO device_address(device_id, name, value) VALUES(4, 'ptmx_fops', '0xc0e3bed8');
  INSERT INTO device_address(device_id, name, value) VALUES(4, 'perf_swevent_enabled', '0xc0e219b4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(5, 'C5306', '12.0.A.1.284', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(5, 'prepare_kernel_cred', '0xc009ec08');
  INSERT INTO device_address(device_id, name, value) VALUES(5, 'commit_creds', '0xc009e72c');
  INSERT INTO device_address(device_id, name, value) VALUES(5, 'remap_pfn_range', '0xc011445c');
  INSERT INTO device_address(device_id, name, value) VALUES(5, 'ptmx_fops', '0xc0e3bed8');
  INSERT INTO device_address(device_id, name, value) VALUES(5, 'perf_swevent_enabled', '0xc0e219b4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(6, 'C5306', '12.0.A.1.257', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(6, 'prepare_kernel_cred', '0xc009ec08');
  INSERT INTO device_address(device_id, name, value) VALUES(6, 'commit_creds', '0xc009e72c');
  INSERT INTO device_address(device_id, name, value) VALUES(6, 'remap_pfn_range', '0xc011445c');
  INSERT INTO device_address(device_id, name, value) VALUES(6, 'ptmx_fops', '0xc0e3b890');
  INSERT INTO device_address(device_id, name, value) VALUES(6, 'perf_swevent_enabled', '0xc0e21374');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(7, 'C5303', '12.0.A.1.257', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(7, 'prepare_kernel_cred', '0xc009ec08');
  INSERT INTO device_address(device_id, name, value) VALUES(7, 'commit_creds', '0xc009e72c');
  INSERT INTO device_address(device_id, name, value) VALUES(7, 'remap_pfn_range', '0xc011445c');
  INSERT INTO device_address(device_id, name, value) VALUES(7, 'ptmx_fops', '0xc0e3b890');
  INSERT INTO device_address(device_id, name, value) VALUES(7, 'perf_swevent_enabled', '0xc0e21374');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(8, 'C5302', '12.0.A.1.257', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(8, 'prepare_kernel_cred', '0xc009ec08');
  INSERT INTO device_address(device_id, name, value) VALUES(8, 'commit_creds', '0xc009e72c');
  INSERT INTO device_address(device_id, name, value) VALUES(8, 'remap_pfn_range', '0xc011445c');
  INSERT INTO device_address(device_id, name, value) VALUES(8, 'ptmx_fops', '0xc0e3b890');
  INSERT INTO device_address(device_id, name, value) VALUES(8, 'perf_swevent_enabled', '0xc0e21374');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(9, 'C5306', '12.0.A.1.211', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(9, 'prepare_kernel_cred', '0xc009ec08');
  INSERT INTO device_address(device_id, name, value) VALUES(9, 'commit_creds', '0xc009e72c');
  INSERT INTO device_address(device_id, name, value) VALUES(9, 'remap_pfn_range', '0xc011445c');
  INSERT INTO device_address(device_id, name, value) VALUES(9, 'ptmx_fops', '0xc0e3b8d0');
  INSERT INTO device_address(device_id, name, value) VALUES(9, 'perf_swevent_enabled', '0xc0e213b4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(10, 'C5303', '12.0.A.1.211', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(10, 'prepare_kernel_cred', '0xc009ec08');
  INSERT INTO device_address(device_id, name, value) VALUES(10, 'commit_creds', '0xc009e72c');
  INSERT INTO device_address(device_id, name, value) VALUES(10, 'remap_pfn_range', '0xc011445c');
  INSERT INTO device_address(device_id, name, value) VALUES(10, 'ptmx_fops', '0xc0e3b8d0');
  INSERT INTO device_address(device_id, name, value) VALUES(10, 'perf_swevent_enabled', '0xc0e213b4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(11, 'C5302', '12.0.A.1.211', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(11, 'prepare_kernel_cred', '0xc009ec08');
  INSERT INTO device_address(device_id, name, value) VALUES(11, 'commit_creds', '0xc009e72c');
  INSERT INTO device_address(device_id, name, value) VALUES(11, 'remap_pfn_range', '0xc011445c');
  INSERT INTO device_address(device_id, name, value) VALUES(11, 'ptmx_fops', '0xc0e3b8d0');
  INSERT INTO device_address(device_id, name, value) VALUES(11, 'perf_swevent_enabled', '0xc0e213b4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(12, 'M35h', '12.0.A.1.257', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(12, 'prepare_kernel_cred', '0xc009ec08');
  INSERT INTO device_address(device_id, name, value) VALUES(12, 'commit_creds', '0xc009e72c');
  INSERT INTO device_address(device_id, name, value) VALUES(12, 'remap_pfn_range', '0xc011445c');
  INSERT INTO device_address(device_id, name, value) VALUES(12, 'ptmx_fops', '0xc0e3b890');
  INSERT INTO device_address(device_id, name, value) VALUES(12, 'perf_swevent_enabled', '0xc0e21374');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(13, 'C2104', '15.0.A.1.31', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(13, 'prepare_kernel_cred', '0xc0092570');
  INSERT INTO device_address(device_id, name, value) VALUES(13, 'commit_creds', '0xc0092094');
  INSERT INTO device_address(device_id, name, value) VALUES(13, 'remap_pfn_range', '0xc00e8414');
  INSERT INTO device_address(device_id, name, value) VALUES(13, 'ptmx_fops', '0xc0f02640');
  INSERT INTO device_address(device_id, name, value) VALUES(13, 'perf_swevent_enabled', '0xc0eece2c');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(14, 'C2105', '15.0.A.1.31', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(14, 'prepare_kernel_cred', '0xc0092570');
  INSERT INTO device_address(device_id, name, value) VALUES(14, 'commit_creds', '0xc0092094');
  INSERT INTO device_address(device_id, name, value) VALUES(14, 'remap_pfn_range', '0xc00e8414');
  INSERT INTO device_address(device_id, name, value) VALUES(14, 'ptmx_fops', '0xc0f02640');
  INSERT INTO device_address(device_id, name, value) VALUES(14, 'perf_swevent_enabled', '0xc0eece2c');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(15, 'C2104', '15.0.A.1.36', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(15, 'prepare_kernel_cred', '0xc0092570');
  INSERT INTO device_address(device_id, name, value) VALUES(15, 'commit_creds', '0xc0092094');
  INSERT INTO device_address(device_id, name, value) VALUES(15, 'remap_pfn_range', '0xc00e8414');
  INSERT INTO device_address(device_id, name, value) VALUES(15, 'ptmx_fops', '0xc0f02640');
  INSERT INTO device_address(device_id, name, value) VALUES(15, 'perf_swevent_enabled', '0xc0eece2c');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(16, 'C2105', '15.0.A.1.36', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(16, 'prepare_kernel_cred', '0xc0092570');
  INSERT INTO device_address(device_id, name, value) VALUES(16, 'commit_creds', '0xc0092094');
  INSERT INTO device_address(device_id, name, value) VALUES(16, 'remap_pfn_range', '0xc00e8414');
  INSERT INTO device_address(device_id, name, value) VALUES(16, 'ptmx_fops', '0xc0f02640');
  INSERT INTO device_address(device_id, name, value) VALUES(16, 'perf_swevent_enabled', '0xc0eece2c');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(17, 'C6616', '10.1.1.A.1.319', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(17, 'prepare_kernel_cred', '0xc0093de4');
  INSERT INTO device_address(device_id, name, value) VALUES(17, 'commit_creds', '0xc0093908');
  INSERT INTO device_address(device_id, name, value) VALUES(17, 'remap_pfn_range', '0xc01098a4');
  INSERT INTO device_address(device_id, name, value) VALUES(17, 'ptmx_fops', '0xc0d37488');
  INSERT INTO device_address(device_id, name, value) VALUES(17, 'perf_swevent_enabled', '0xc0d1fcb4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(18, 'C6606', '10.1.1.B.0.166', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(18, 'prepare_kernel_cred', '0xc0093dd4');
  INSERT INTO device_address(device_id, name, value) VALUES(18, 'commit_creds', '0xc00938f8');
  INSERT INTO device_address(device_id, name, value) VALUES(18, 'remap_pfn_range', '0xc0109894');
  INSERT INTO device_address(device_id, name, value) VALUES(18, 'ptmx_fops', '0xc0d37488');
  INSERT INTO device_address(device_id, name, value) VALUES(18, 'perf_swevent_enabled', '0xc0d1fcb4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(19, 'C6603', '10.3.A.0.423', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(19, 'prepare_kernel_cred', '0xc009a740');
  INSERT INTO device_address(device_id, name, value) VALUES(19, 'commit_creds', '0xc009a264');
  INSERT INTO device_address(device_id, name, value) VALUES(19, 'remap_pfn_range', '0xc0111f48');
  INSERT INTO device_address(device_id, name, value) VALUES(19, 'ptmx_fops', '0xc0e46fd0');
  INSERT INTO device_address(device_id, name, value) VALUES(19, 'perf_swevent_enabled', '0xc0e27e74');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(20, 'C6602', '10.3.A.0.423', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(20, 'prepare_kernel_cred', '0xc009a740');
  INSERT INTO device_address(device_id, name, value) VALUES(20, 'commit_creds', '0xc009a264');
  INSERT INTO device_address(device_id, name, value) VALUES(20, 'remap_pfn_range', '0xc0111f48');
  INSERT INTO device_address(device_id, name, value) VALUES(20, 'ptmx_fops', '0xc0e46fd0');
  INSERT INTO device_address(device_id, name, value) VALUES(20, 'perf_swevent_enabled', '0xc0e27e74');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(21, 'C6603', '10.1.1.A.1.307', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(21, 'prepare_kernel_cred', '0xc0093dd4');
  INSERT INTO device_address(device_id, name, value) VALUES(21, 'commit_creds', '0xc00938f8');
  INSERT INTO device_address(device_id, name, value) VALUES(21, 'remap_pfn_range', '0xc0109894');
  INSERT INTO device_address(device_id, name, value) VALUES(21, 'ptmx_fops', '0xc0d37488');
  INSERT INTO device_address(device_id, name, value) VALUES(21, 'perf_swevent_enabled', '0xc0d1fcb4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(22, 'C6602', '10.1.1.A.1.307', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(22, 'prepare_kernel_cred', '0xc0093dd4');
  INSERT INTO device_address(device_id, name, value) VALUES(22, 'commit_creds', '0xc00938f8');
  INSERT INTO device_address(device_id, name, value) VALUES(22, 'remap_pfn_range', '0xc0109894');
  INSERT INTO device_address(device_id, name, value) VALUES(22, 'ptmx_fops', '0xc0d37488');
  INSERT INTO device_address(device_id, name, value) VALUES(22, 'perf_swevent_enabled', '0xc0d1fcb4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(23, 'C6603', '10.1.1.A.1.253', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(23, 'prepare_kernel_cred', '0xc0093dd4');
  INSERT INTO device_address(device_id, name, value) VALUES(23, 'commit_creds', '0xc00938f8');
  INSERT INTO device_address(device_id, name, value) VALUES(23, 'remap_pfn_range', '0xc0109894');
  INSERT INTO device_address(device_id, name, value) VALUES(23, 'ptmx_fops', '0xc0d37488');
  INSERT INTO device_address(device_id, name, value) VALUES(23, 'perf_swevent_enabled', '0xc0d1fcb4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(24, 'C6602', '10.1.1.A.1.253', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(24, 'prepare_kernel_cred', '0xc0093dd4');
  INSERT INTO device_address(device_id, name, value) VALUES(24, 'commit_creds', '0xc00938f8');
  INSERT INTO device_address(device_id, name, value) VALUES(24, 'remap_pfn_range', '0xc0109894');
  INSERT INTO device_address(device_id, name, value) VALUES(24, 'ptmx_fops', '0xc0d37488');
  INSERT INTO device_address(device_id, name, value) VALUES(24, 'perf_swevent_enabled', '0xc0d1fcb4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(25, 'C6503', '10.3.A.0.423', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(25, 'prepare_kernel_cred', '0xc009ae60');
  INSERT INTO device_address(device_id, name, value) VALUES(25, 'commit_creds', '0xc009a984');
  INSERT INTO device_address(device_id, name, value) VALUES(25, 'remap_pfn_range', '0xc0112668');
  INSERT INTO device_address(device_id, name, value) VALUES(25, 'ptmx_fops', '0xc0e46ce0');
  INSERT INTO device_address(device_id, name, value) VALUES(25, 'perf_swevent_enabled', '0xc0e27c74');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(26, 'C6502', '10.3.A.0.423', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(26, 'prepare_kernel_cred', '0xc009ae60');
  INSERT INTO device_address(device_id, name, value) VALUES(26, 'commit_creds', '0xc009a984');
  INSERT INTO device_address(device_id, name, value) VALUES(26, 'remap_pfn_range', '0xc0112668');
  INSERT INTO device_address(device_id, name, value) VALUES(26, 'ptmx_fops', '0xc0e46ce0');
  INSERT INTO device_address(device_id, name, value) VALUES(26, 'perf_swevent_enabled', '0xc0e27c74');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(27, 'C6506', '10.3.A.0.423', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(27, 'prepare_kernel_cred', '0xc009ae60');
  INSERT INTO device_address(device_id, name, value) VALUES(27, 'commit_creds', '0xc009a984');
  INSERT INTO device_address(device_id, name, value) VALUES(27, 'remap_pfn_range', '0xc0112668');
  INSERT INTO device_address(device_id, name, value) VALUES(27, 'ptmx_fops', '0xc0e46ce0');
  INSERT INTO device_address(device_id, name, value) VALUES(27, 'perf_swevent_enabled', '0xc0e27c74');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(28, 'F-02E', 'V16R46A', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(28, 'prepare_kernel_cred', '0xc00a0cdc');
  INSERT INTO device_address(device_id, name, value) VALUES(28, 'commit_creds', '0xc00a0660');
  INSERT INTO device_address(device_id, name, value) VALUES(28, 'remap_pfn_range', '0xc011272c');
  INSERT INTO device_address(device_id, name, value) VALUES(28, 'ptmx_fops', '0xc0ca1ca8');
  INSERT INTO device_address(device_id, name, value) VALUES(28, 'perf_swevent_enabled', '0xc0c8411c');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(29, 'F-02E', 'V17R48A', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(29, 'prepare_kernel_cred', '0xc00a0cf0');
  INSERT INTO device_address(device_id, name, value) VALUES(29, 'commit_creds', '0xc00a0674');
  INSERT INTO device_address(device_id, name, value) VALUES(29, 'remap_pfn_range', '0xc0112740');
  INSERT INTO device_address(device_id, name, value) VALUES(29, 'ptmx_fops', '0xc0ca1ca8');
  INSERT INTO device_address(device_id, name, value) VALUES(29, 'perf_swevent_enabled', '0xc0c8411c');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(30, 'F-02E', 'V19R50D', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(30, 'prepare_kernel_cred', '0xc00a0cec');
  INSERT INTO device_address(device_id, name, value) VALUES(30, 'commit_creds', '0xc00a0670');
  INSERT INTO device_address(device_id, name, value) VALUES(30, 'remap_pfn_range', '0xc0112744');
  INSERT INTO device_address(device_id, name, value) VALUES(30, 'vmalloc_exec', '0xc012051c');
  INSERT INTO device_address(device_id, name, value) VALUES(30, 'ptmx_fops', '0xc0ca1d28');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(31, 'F-03D', 'V24R33Cc', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(31, 'delayed_rsp_id', '0xc0777dd0');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(32, 'F-04E', 'V08R39A', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(32, 'prepare_kernel_cred', '0xc0092758');
  INSERT INTO device_address(device_id, name, value) VALUES(32, 'commit_creds', '0xc0092114');
  INSERT INTO device_address(device_id, name, value) VALUES(32, 'remap_pfn_range', '0xc00e3a44');
  INSERT INTO device_address(device_id, name, value) VALUES(32, 'vmalloc_exec', '0xc00f1140');
  INSERT INTO device_address(device_id, name, value) VALUES(32, 'ptmx_fops', '0xc0b955f4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(33, 'F-05D', 'V08R31C', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(33, 'ptmx_fops', '0xc07bc164');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(34, 'F-05D', 'V11R40A', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(34, 'ptmx_fops', '0xc07bbf44');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(35, 'F-06E', 'V21R48D', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(35, 'prepare_kernel_cred', '0xc00ab27c');
  INSERT INTO device_address(device_id, name, value) VALUES(35, 'commit_creds', '0xc00aad54');
  INSERT INTO device_address(device_id, name, value) VALUES(35, 'remap_pfn_range', '0xc012341c');
  INSERT INTO device_address(device_id, name, value) VALUES(35, 'ptmx_fops', '0xc10d7774');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(36, 'F-07E', 'V19R38A', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(36, 'prepare_kernel_cred', '0xc00ab10c');
  INSERT INTO device_address(device_id, name, value) VALUES(36, 'commit_creds', '0xc00aabe4');
  INSERT INTO device_address(device_id, name, value) VALUES(36, 'remap_pfn_range', '0xc01232ac');
  INSERT INTO device_address(device_id, name, value) VALUES(36, 'vmalloc_exec', '0xc012fd64');
  INSERT INTO device_address(device_id, name, value) VALUES(36, 'ptmx_fops', '0xc10d75b4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(37, 'F-07E', 'V20R39D', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(37, 'prepare_kernel_cred', '0xc00ab12c');
  INSERT INTO device_address(device_id, name, value) VALUES(37, 'commit_creds', '0xc00aac04');
  INSERT INTO device_address(device_id, name, value) VALUES(37, 'remap_pfn_range', '0xc01232cc');
  INSERT INTO device_address(device_id, name, value) VALUES(37, 'vmalloc_exec', '0xc012fd84');
  INSERT INTO device_address(device_id, name, value) VALUES(37, 'ptmx_fops', '0xc10d7634');
  INSERT INTO device_address(device_id, name, value) VALUES(37, 'security_remap_pfn_range', '0xc027eee8');
  INSERT INTO device_address(device_id, name, value) VALUES(37, 'remap_pfn_range_end_op', '0xc0f6792c');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(38, 'F-07E', 'V21R40B', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(38, 'prepare_kernel_cred', '0xc00ab12c');
  INSERT INTO device_address(device_id, name, value) VALUES(38, 'commit_creds', '0xc00aac04');
  INSERT INTO device_address(device_id, name, value) VALUES(38, 'remap_pfn_range', '0xc01232cc');
  INSERT INTO device_address(device_id, name, value) VALUES(38, 'vmalloc_exec', '0xc012fd84');
  INSERT INTO device_address(device_id, name, value) VALUES(38, 'ptmx_fops', '0xc10d7634');
  INSERT INTO device_address(device_id, name, value) VALUES(38, 'security_remap_pfn_range', '0xc027eee8');
  INSERT INTO device_address(device_id, name, value) VALUES(38, 'remap_pfn_range_end_op', '0xc0f6792c');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(39, 'F-10D', 'V10R42A', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(39, 'prepare_kernel_cred', '0xc00927b0');
  INSERT INTO device_address(device_id, name, value) VALUES(39, 'commit_creds', '0xc0092248');
  INSERT INTO device_address(device_id, name, value) VALUES(39, 'remap_pfn_range', '0xc00e38e8');
  INSERT INTO device_address(device_id, name, value) VALUES(39, 'vmalloc_exec', '0xc00f0fe4');
  INSERT INTO device_address(device_id, name, value) VALUES(39, 'ptmx_fops', '0xc0b7755c');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(40, 'F-10D', 'V21R48A', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(40, 'ptmx_fops', '0xc09a60e0');
  INSERT INTO device_address(device_id, name, value) VALUES(40, 'perf_swevent_enabled', '0xc09882f4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(41, 'F-10D', 'V22R49C', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(41, 'ptmx_fops', '0xc09a60bc');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(42, 'F-11D', 'V21R36A', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(42, 'delayed_rsp_id', '0xc092f1a4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(43, 'F-11D', 'V24R40A', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(43, 'ptmx_fops', '0xc1056998');
  INSERT INTO device_address(device_id, name, value) VALUES(43, 'delayed_rsp_id', '0xc091bf8c');
  INSERT INTO device_address(device_id, name, value) VALUES(43, 'perf_swevent_enabled', '0xc104cf1c');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(44, 'F-11D', 'V26R42B', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(44, 'delayed_rsp_id', '0xc091bf8c');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(45, 'F-12C', 'V21', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(45, 'delayed_rsp_id', '0xc075aca4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(46, 'FJL21', 'V23R39X', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(46, 'ptmx_fops', '0xc0ee31f8');
  INSERT INTO device_address(device_id, name, value) VALUES(46, 'perf_swevent_enabled', '0xc0ec1da0');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(47, 'FJL21', 'V37R47A', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(47, 'ptmx_fops', '0xc0ee3378');
  INSERT INTO device_address(device_id, name, value) VALUES(47, 'perf_swevent_enabled', '0xc0ec1f20');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(48, 'FJL21', 'V39R48C', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(48, 'ptmx_fops', '0xc0ee3378');
  INSERT INTO device_address(device_id, name, value) VALUES(48, 'perf_swevent_enabled', '0xc0ec1f20');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(49, 'HTC6600LVW', 'JSS15J', 'ro.aa.romver', '1.11.605.4');
  INSERT INTO device_address(device_id, name, value) VALUES(49, 'prepare_kernel_cred', '0xc00c3638');
  INSERT INTO device_address(device_id, name, value) VALUES(49, 'commit_creds', '0xc00c3100');
  INSERT INTO device_address(device_id, name, value) VALUES(49, 'remap_pfn_range', '0xc0144664');
  INSERT INTO device_address(device_id, name, value) VALUES(49, 'vmalloc_exec', '0xc0150cc8');
  INSERT INTO device_address(device_id, name, value) VALUES(49, 'ptmx_fops', '0xc0f1d834');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(50, 'HTL21', 'JRO03C', 'ro.aa.romver', '1.29.970.1');
  INSERT INTO device_address(device_id, name, value) VALUES(50, 'prepare_kernel_cred', '0xc00ab9d8');
  INSERT INTO device_address(device_id, name, value) VALUES(50, 'commit_creds', '0xc00ab4c4');
  INSERT INTO device_address(device_id, name, value) VALUES(50, 'remap_pfn_range', '0xc00ff32c');
  INSERT INTO device_address(device_id, name, value) VALUES(50, 'vmalloc_exec', '0xc010b728');
  INSERT INTO device_address(device_id, name, value) VALUES(50, 'ptmx_fops', '0xc0d1d944');
  INSERT INTO device_address(device_id, name, value) VALUES(50, 'perf_swevent_enabled', '0xc0d07a7c');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(51, 'HTL21', 'JRO03C', 'ro.aa.romver', '1.36.970.1');
  INSERT INTO device_address(device_id, name, value) VALUES(51, 'prepare_kernel_cred', '0xc00abd48');
  INSERT INTO device_address(device_id, name, value) VALUES(51, 'commit_creds', '0xc00ab834');
  INSERT INTO device_address(device_id, name, value) VALUES(51, 'remap_pfn_range', '0xc00ff6a4');
  INSERT INTO device_address(device_id, name, value) VALUES(51, 'vmalloc_exec', '0xc010baa0');
  INSERT INTO device_address(device_id, name, value) VALUES(51, 'ptmx_fops', '0xc0d1dec4');
  INSERT INTO device_address(device_id, name, value) VALUES(51, 'msm_acdb.value_pos', 100);
  INSERT INTO device_address(device_id, name, value) VALUES(51, 'msm_acdb.address_pos', 112);
  INSERT INTO device_address(device_id, name, value) VALUES(51, 'msm_acdb.pc1.pos', 116);
  INSERT INTO device_address(device_id, name, value) VALUES(51, 'msm_acdb.pc1.value', '0xc01e27a4');
  INSERT INTO device_address(device_id, name, value) VALUES(51, 'msm_acdb.pc2.pos', 148);
  INSERT INTO device_address(device_id, name, value) VALUES(51, 'msm_acdb.pc2.value', '0xc000dd0c');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(52, 'HTL21', 'JRO03C', 'ro.aa.romver', '1.39.970.1');
  INSERT INTO device_address(device_id, name, value) VALUES(52, 'prepare_kernel_cred', '0xc00abdd8');
  INSERT INTO device_address(device_id, name, value) VALUES(52, 'commit_creds', '0xc00ab8c4');
  INSERT INTO device_address(device_id, name, value) VALUES(52, 'remap_pfn_range', '0xc00ff734');
  INSERT INTO device_address(device_id, name, value) VALUES(52, 'vmalloc_exec', '0xc0d1df3c');
  INSERT INTO device_address(device_id, name, value) VALUES(52, 'ptmx_fops', '0xc0d1df44');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(53, 'HTL22', 'JZO54K', 'ro.aa.romver', '1.05.970.2');
  INSERT INTO device_address(device_id, name, value) VALUES(53, 'prepare_kernel_cred', '0xc00b2688');
  INSERT INTO device_address(device_id, name, value) VALUES(53, 'commit_creds', '0xc00b2174');
  INSERT INTO device_address(device_id, name, value) VALUES(53, 'remap_pfn_range', '0xc0128b10');
  INSERT INTO device_address(device_id, name, value) VALUES(53, 'ptmx_fops', '0xc0df467c');
  INSERT INTO device_address(device_id, name, value) VALUES(53, 'perf_swevent_enabled', '0xc0ddd7a4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(54, 'HTL22', 'JZO54K', 'ro.aa.romver', '1.07.970.4');
  INSERT INTO device_address(device_id, name, value) VALUES(54, 'prepare_kernel_cred', '0xc00b26a0');
  INSERT INTO device_address(device_id, name, value) VALUES(54, 'commit_creds', '0xc00b218c');
  INSERT INTO device_address(device_id, name, value) VALUES(54, 'remap_pfn_range', '0xc0128b28');
  INSERT INTO device_address(device_id, name, value) VALUES(54, 'ptmx_fops', '0xc0df52bc');
  INSERT INTO device_address(device_id, name, value) VALUES(54, 'perf_swevent_enabled', '0xc0dde3e4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(55, 'HTL22', 'JDQ39', 'ro.aa.romver', '2.15.970.1');
  INSERT INTO device_address(device_id, name, value) VALUES(55, 'prepare_kernel_cred', '0xc00b3664');
  INSERT INTO device_address(device_id, name, value) VALUES(55, 'commit_creds', '0xc00b3150');
  INSERT INTO device_address(device_id, name, value) VALUES(55, 'remap_pfn_range', '0xc012a37c');
  INSERT INTO device_address(device_id, name, value) VALUES(55, 'vmalloc_exec', '0xc0136854');
  INSERT INTO device_address(device_id, name, value) VALUES(55, 'ptmx_fops', '0xc0ef7d44');
  INSERT INTO device_address(device_id, name, value) VALUES(55, 'msm_acdb.value_pos', 100);
  INSERT INTO device_address(device_id, name, value) VALUES(55, 'msm_acdb.address_pos', 112);
  INSERT INTO device_address(device_id, name, value) VALUES(55, 'msm_acdb.pc1.pos', 116);
  INSERT INTO device_address(device_id, name, value) VALUES(55, 'msm_acdb.pc1.value', '0xc022acb8');
  INSERT INTO device_address(device_id, name, value) VALUES(55, 'msm_acdb.pc2.pos', 148);
  INSERT INTO device_address(device_id, name, value) VALUES(55, 'msm_acdb.pc2.value', '0xc000ddac');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(56, 'HTL22', 'JDQ39', 'ro.aa.romver', '2.21.970.2');
  INSERT INTO device_address(device_id, name, value) VALUES(56, 'prepare_kernel_cred', '0xc00b40b0');
  INSERT INTO device_address(device_id, name, value) VALUES(56, 'commit_creds', '0xc00b3b9c');
  INSERT INTO device_address(device_id, name, value) VALUES(56, 'remap_pfn_range', '0xc012afc0');
  INSERT INTO device_address(device_id, name, value) VALUES(56, 'vmalloc_exec', '0xc0137498');
  INSERT INTO device_address(device_id, name, value) VALUES(56, 'ptmx_fops', '0xc0efc244');
  INSERT INTO device_address(device_id, name, value) VALUES(56, 'msm_acdb.value_pos', 100);
  INSERT INTO device_address(device_id, name, value) VALUES(56, 'msm_acdb.address_pos', 112);
  INSERT INTO device_address(device_id, name, value) VALUES(56, 'msm_acdb.pc1.pos', 116);
  INSERT INTO device_address(device_id, name, value) VALUES(56, 'msm_acdb.pc1.value', '0xc022bcd8');
  INSERT INTO device_address(device_id, name, value) VALUES(56, 'msm_acdb.pc2.pos', 148);
  INSERT INTO device_address(device_id, name, value) VALUES(56, 'msm_acdb.pc2.value', '0xc000ddbc');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(57, 'HTX21', 'JRO03C', 'ro.aa.romver', '1.20.971.1');
  INSERT INTO device_address(device_id, name, value) VALUES(57, 'prepare_kernel_cred', '0xc00a6e54');
  INSERT INTO device_address(device_id, name, value) VALUES(57, 'commit_creds', '0xc00a6940');
  INSERT INTO device_address(device_id, name, value) VALUES(57, 'remap_pfn_range', '0xc00fa8b0');
  INSERT INTO device_address(device_id, name, value) VALUES(57, 'ptmx_fops', '0xc0ccc0b4');
  INSERT INTO device_address(device_id, name, value) VALUES(57, 'perf_swevent_enabled', '0xc0cb513c');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(58, 'HTX21', 'JRO03C', 'ro.aa.romver', '1.25.971.1');
  INSERT INTO device_address(device_id, name, value) VALUES(58, 'prepare_kernel_cred', '0xc00a7460');
  INSERT INTO device_address(device_id, name, value) VALUES(58, 'commit_creds', '0xc00a6f4c');
  INSERT INTO device_address(device_id, name, value) VALUES(58, 'remap_pfn_range', '0xc00faec4');
  INSERT INTO device_address(device_id, name, value) VALUES(58, 'ptmx_fops', '0xc0ccc134');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(59, 'IS11N', 'GRJ90', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(59, 'delayed_rsp_id', '0xc0835758');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(60, 'IS12S', '6.1.D.1.91', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(60, 'prepare_kernel_cred', '0xc01b6a40');
  INSERT INTO device_address(device_id, name, value) VALUES(60, 'commit_creds', '0xc01b6348');
  INSERT INTO device_address(device_id, name, value) VALUES(60, 'remap_pfn_range', '0xc02259c4');
  INSERT INTO device_address(device_id, name, value) VALUES(60, 'ptmx_fops', '0xc0c9b7c0');
  INSERT INTO device_address(device_id, name, value) VALUES(60, 'perf_swevent_enabled', '0xc0c902e8');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(61, 'IS12S', '6.1.D.1.103', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(61, 'prepare_kernel_cred', '0xc01b6a58');
  INSERT INTO device_address(device_id, name, value) VALUES(61, 'commit_creds', '0xc01b6360');
  INSERT INTO device_address(device_id, name, value) VALUES(61, 'remap_pfn_range', '0xc0225a20');
  INSERT INTO device_address(device_id, name, value) VALUES(61, 'ptmx_fops', '0xc0c9b7c0');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(62, 'IS15SH', '01.00.04', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(62, 'prepare_kernel_cred', '0xc01c6178');
  INSERT INTO device_address(device_id, name, value) VALUES(62, 'commit_creds', '0xc01c643c');
  INSERT INTO device_address(device_id, name, value) VALUES(62, 'remap_pfn_range', '0xc0208980');
  INSERT INTO device_address(device_id, name, value) VALUES(62, 'ptmx_fops', '0xc0edaf90');
  INSERT INTO device_address(device_id, name, value) VALUES(62, 'perf_swevent_enabled', '0xc0ecc17c');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(63, 'IS17SH', '01.00.03', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(63, 'delayed_rsp_id', '0xc0a546fc');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(64, 'IS17SH', '01.00.04', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(64, 'kernel_physical_offset', '0x00208000');
  INSERT INTO device_address(device_id, name, value) VALUES(64, 'prepare_kernel_cred', '0xc01c66a8');
  INSERT INTO device_address(device_id, name, value) VALUES(64, 'commit_creds', '0xc01c5fd8');
  INSERT INTO device_address(device_id, name, value) VALUES(64, 'remap_pfn_range', '0xc0208a34');
  INSERT INTO device_address(device_id, name, value) VALUES(64, 'vmalloc_exec', '0xc0212b70');
  INSERT INTO device_address(device_id, name, value) VALUES(64, 'ptmx_fops', '0xc0edae90');
  INSERT INTO device_address(device_id, name, value) VALUES(64, 'perf_swevent_enabled', '0xc0ecbebc');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(65, 'ISW11F', 'FIK700', 'gsm.version.baseband', 'V25R45A');
  INSERT INTO device_address(device_id, name, value) VALUES(65, 'ptmx_fops', '0xc080e268');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(66, 'ISW11F', 'FIK700', 'gsm.version.baseband', 'V27R47I');
  INSERT INTO device_address(device_id, name, value) VALUES(66, 'ptmx_fops', '0xc080e028');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(67, 'ISW11K', '145.0.0002', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(67, 'delayed_rsp_id', '0xc07f93a4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(68, 'URBANO PROGRESSO', '010.0.3000', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(68, 'ptmx_fops', '0xc0dc0a10');
  INSERT INTO device_address(device_id, name, value) VALUES(68, 'delayed_rsp_id', '0xc0935104');
  INSERT INTO device_address(device_id, name, value) VALUES(68, 'perf_swevent_enabled', '0xc0db6244');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(69, 'URBANO PROGRESSO', '011.0.3100', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(69, 'ptmx_fops', '0xc0dc0a10');
  INSERT INTO device_address(device_id, name, value) VALUES(69, 'perf_swevent_enabled', '0xc0db6244');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(70, 'ISW13F', 'V69R51I', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(70, 'ptmx_fops', '0xc09fc600');
  INSERT INTO device_address(device_id, name, value) VALUES(70, 'perf_swevent_enabled', '0xc09de374');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(71, 'ISW13F', 'V75R58A', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(71, 'ptmx_fops', '0xc09fa200');
  INSERT INTO device_address(device_id, name, value) VALUES(71, 'perf_swevent_enabled', '0xc09dbf74');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(72, 'ISW13HT', 'IMM76D', 'ro.aa.romver', '2.06.970.4');
  INSERT INTO device_address(device_id, name, value) VALUES(72, 'prepare_kernel_cred', '0xc01a3be0');
  INSERT INTO device_address(device_id, name, value) VALUES(72, 'commit_creds', '0xc01a3494');
  INSERT INTO device_address(device_id, name, value) VALUES(72, 'remap_pfn_range', '0xc0205c80');
  INSERT INTO device_address(device_id, name, value) VALUES(72, 'ptmx_fops', '0xc127a8b0');
  INSERT INTO device_address(device_id, name, value) VALUES(72, 'perf_swevent_enabled', '0xc126e608');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(73, 'L-01D', 'IMM76D', 'ro.lge.swversion', 'L01D-V20c-AUG-29-2012');
  INSERT INTO device_address(device_id, name, value) VALUES(73, 'perf_swevent_enabled', '0xc1140768');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(74, 'L-01D', 'IMM76D', 'ro.lge.swversion', 'L01D-V20d-FEB-15-2013');
  INSERT INTO device_address(device_id, name, value) VALUES(74, 'perf_swevent_enabled', '0xc1140768');
  INSERT INTO device_address(device_id, name, value) VALUES(74, 'msm_acdb.value_pos', 104);
  INSERT INTO device_address(device_id, name, value) VALUES(74, 'msm_acdb.address_pos', 120);
  INSERT INTO device_address(device_id, name, value) VALUES(74, 'msm_acdb.pc1.pos', 132);
  INSERT INTO device_address(device_id, name, value) VALUES(74, 'msm_acdb.pc1.value', '0xc0417b30');
  INSERT INTO device_address(device_id, name, value) VALUES(74, 'msm_acdb.pc2.pos', 164);
  INSERT INTO device_address(device_id, name, value) VALUES(74, 'msm_acdb.pc2.value', '0xc0381064');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(75, 'L-01D', 'IMM76D', 'ro.lge.swversion', 'L01D-V20e-OCT-22-2013');
  INSERT INTO device_address(device_id, name, value) VALUES(75, 'msm_acdb.value_pos', 104);
  INSERT INTO device_address(device_id, name, value) VALUES(75, 'msm_acdb.address_pos', 120);
  INSERT INTO device_address(device_id, name, value) VALUES(75, 'msm_acdb.pc1.pos', 132);
  INSERT INTO device_address(device_id, name, value) VALUES(75, 'msm_acdb.pc1.value', '0xc0417bf0');
  INSERT INTO device_address(device_id, name, value) VALUES(75, 'msm_acdb.pc2.pos', 164);
  INSERT INTO device_address(device_id, name, value) VALUES(75, 'msm_acdb.pc2.value', '0xc03810ac');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(76, 'L-01E', 'IMM76L', 'ro.lge.swversion', 'L01E10c');
  INSERT INTO device_address(device_id, name, value) VALUES(76, 'prepare_kernel_cred', '0xc01aa40c');
  INSERT INTO device_address(device_id, name, value) VALUES(76, 'commit_creds', '0xc01aa570');
  INSERT INTO device_address(device_id, name, value) VALUES(76, 'remap_pfn_range', '0xc020d08c');
  INSERT INTO device_address(device_id, name, value) VALUES(76, 'ptmx_fops', '0xc0e715c8');
  INSERT INTO device_address(device_id, name, value) VALUES(76, 'perf_swevent_enabled', '0xc0e59920');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(77, 'L-01F', 'JDQ39B', 'ro.lge.swversion', 'L01F10c');
  INSERT INTO device_address(device_id, name, value) VALUES(77, 'prepare_kernel_cred', '0xc00c37a8');
  INSERT INTO device_address(device_id, name, value) VALUES(77, 'commit_creds', '0xc00c329c');
  INSERT INTO device_address(device_id, name, value) VALUES(77, 'remap_pfn_range', '0xc0144c20');
  INSERT INTO device_address(device_id, name, value) VALUES(77, 'vmalloc_exec', '0xc01521dc');
  INSERT INTO device_address(device_id, name, value) VALUES(77, 'ptmx_fops', '0xc101c490');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(78, 'L-02E', 'IMM76L', 'ro.lge.swversion', 'L02E10c');
  INSERT INTO device_address(device_id, name, value) VALUES(78, 'perf_swevent_enabled', '0xc0c61038');
  INSERT INTO device_address(device_id, name, value) VALUES(78, 'msm_acdb.value_pos', 124);
  INSERT INTO device_address(device_id, name, value) VALUES(78, 'msm_acdb.address_pos', 140);
  INSERT INTO device_address(device_id, name, value) VALUES(78, 'msm_acdb.pc1.pos', 148);
  INSERT INTO device_address(device_id, name, value) VALUES(78, 'msm_acdb.pc1.value', '0xc02dc8c4');
  INSERT INTO device_address(device_id, name, value) VALUES(78, 'msm_acdb.pc2.pos', 180);
  INSERT INTO device_address(device_id, name, value) VALUES(78, 'msm_acdb.pc2.value', '0xc018fd58');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(79, 'L-02E', 'IMM76L', 'ro.lge.swversion', 'L02E10e');
  INSERT INTO device_address(device_id, name, value) VALUES(79, 'perf_swevent_enabled', '0xc0c61038');
  INSERT INTO device_address(device_id, name, value) VALUES(79, 'msm_acdb.value_pos', 124);
  INSERT INTO device_address(device_id, name, value) VALUES(79, 'msm_acdb.address_pos', 140);
  INSERT INTO device_address(device_id, name, value) VALUES(79, 'msm_acdb.pc1.pos', 148);
  INSERT INTO device_address(device_id, name, value) VALUES(79, 'msm_acdb.pc1.value', '0xc02dc984');
  INSERT INTO device_address(device_id, name, value) VALUES(79, 'msm_acdb.pc2.pos', 180);
  INSERT INTO device_address(device_id, name, value) VALUES(79, 'msm_acdb.pc2.value', '0xc018fd6c');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(80, 'L-01E', 'JZO54K', 'ro.lge.swversion', 'L01E20b');
  INSERT INTO device_address(device_id, name, value) VALUES(80, 'prepare_kernel_cred', '0xc009c310');
  INSERT INTO device_address(device_id, name, value) VALUES(80, 'commit_creds', '0xc009beec');
  INSERT INTO device_address(device_id, name, value) VALUES(80, 'remap_pfn_range', '0xc0111c34');
  INSERT INTO device_address(device_id, name, value) VALUES(80, 'vmalloc_exec', '0xc011e860');
  INSERT INTO device_address(device_id, name, value) VALUES(80, 'ptmx_fops', '0xc0fac580');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(81, 'L-02E', 'JZO54K', 'ro.lge.swversion', 'L02E20a');
  INSERT INTO device_address(device_id, name, value) VALUES(81, 'prepare_kernel_cred', '0xc00a2258');
  INSERT INTO device_address(device_id, name, value) VALUES(81, 'commit_creds', '0xc00a1cf8');
  INSERT INTO device_address(device_id, name, value) VALUES(81, 'remap_pfn_range', '0xc01269e0');
  INSERT INTO device_address(device_id, name, value) VALUES(81, 'vmalloc_exec', '0xc01344fc');
  INSERT INTO device_address(device_id, name, value) VALUES(81, 'ptmx_fops', '0xc0d926e0');
  INSERT INTO device_address(device_id, name, value) VALUES(81, 'perf_swevent_enabled', '0xc0d744ec');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(82, 'L-05D', 'JZO54K', 'ro.lge.swversion', 'L05D20c');
  INSERT INTO device_address(device_id, name, value) VALUES(82, 'prepare_kernel_cred', '0xc00a2278');
  INSERT INTO device_address(device_id, name, value) VALUES(82, 'commit_creds', '0xc00a1d18');
  INSERT INTO device_address(device_id, name, value) VALUES(82, 'remap_pfn_range', '0xc01268a4');
  INSERT INTO device_address(device_id, name, value) VALUES(82, 'ptmx_fops', '0xc0d885a8');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(83, 'L-06D', 'IMM76D', 'ro.lge.swversion', 'L06D-V10h-JUL-19-2012');
  INSERT INTO device_address(device_id, name, value) VALUES(83, 'perf_swevent_enabled', '0xc12effa8');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(84, 'L-06D', 'IMM76D', 'ro.lge.swversion', 'L06D-V10k-OCT-17-2012');
  INSERT INTO device_address(device_id, name, value) VALUES(84, 'perf_swevent_enabled', '0xc12f00e8');
  INSERT INTO device_address(device_id, name, value) VALUES(84, 'msm_acdb.value_pos', 104);
  INSERT INTO device_address(device_id, name, value) VALUES(84, 'msm_acdb.address_pos', 120);
  INSERT INTO device_address(device_id, name, value) VALUES(84, 'msm_acdb.pc1.pos', 132);
  INSERT INTO device_address(device_id, name, value) VALUES(84, 'msm_acdb.pc1.value', '0xc041c690');
  INSERT INTO device_address(device_id, name, value) VALUES(84, 'msm_acdb.pc2.pos', 164);
  INSERT INTO device_address(device_id, name, value) VALUES(84, 'msm_acdb.pc2.value', '0xc038c240');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(85, 'L-06D', 'IMM76D', 'ro.lge.swversion', 'L06D-V10p-OCT-09-2013');
  INSERT INTO device_address(device_id, name, value) VALUES(85, 'msm_acdb.value_pos', 104);
  INSERT INTO device_address(device_id, name, value) VALUES(85, 'msm_acdb.address_pos', 120);
  INSERT INTO device_address(device_id, name, value) VALUES(85, 'msm_acdb.pc1.pos', 132);
  INSERT INTO device_address(device_id, name, value) VALUES(85, 'msm_acdb.pc1.value', '0xc041c770');
  INSERT INTO device_address(device_id, name, value) VALUES(85, 'msm_acdb.pc2.pos', 164);
  INSERT INTO device_address(device_id, name, value) VALUES(85, 'msm_acdb.pc2.value', '0xc01031bc');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(86, 'LG-E975', 'JZO54K', 'ro.build.version.incremental', 'E97510e.1366300274');
  INSERT INTO device_address(device_id, name, value) VALUES(86, 'prepare_kernel_cred', '0xc00a0f90');
  INSERT INTO device_address(device_id, name, value) VALUES(86, 'commit_creds', '0xc00a0b6c');
  INSERT INTO device_address(device_id, name, value) VALUES(86, 'remap_pfn_range', '0xc0116598');
  INSERT INTO device_address(device_id, name, value) VALUES(86, 'ptmx_fops', '0xc0f9da70');
  INSERT INTO device_address(device_id, name, value) VALUES(86, 'perf_swevent_enabled', '0xc0f84234');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(87, 'LT28h', '6.2.B.0.211', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(87, 'prepare_kernel_cred', '0xc00c94f8');
  INSERT INTO device_address(device_id, name, value) VALUES(87, 'commit_creds', '0xc00c901c');
  INSERT INTO device_address(device_id, name, value) VALUES(87, 'remap_pfn_range', '0xc014d170');
  INSERT INTO device_address(device_id, name, value) VALUES(87, 'ptmx_fops', '0xc117e328');
  INSERT INTO device_address(device_id, name, value) VALUES(87, 'perf_swevent_enabled', '0xc1169ef4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(88, 'LT28i', '6.2.B.0.211', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(88, 'prepare_kernel_cred', '0xc00c94f8');
  INSERT INTO device_address(device_id, name, value) VALUES(88, 'commit_creds', '0xc00c901c');
  INSERT INTO device_address(device_id, name, value) VALUES(88, 'remap_pfn_range', '0xc014d170');
  INSERT INTO device_address(device_id, name, value) VALUES(88, 'ptmx_fops', '0xc117e328');
  INSERT INTO device_address(device_id, name, value) VALUES(88, 'perf_swevent_enabled', '0xc1169ef4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(89, 'LT26i', '6.2.B.0.200', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(89, 'prepare_kernel_cred', '0xc00b19c8');
  INSERT INTO device_address(device_id, name, value) VALUES(89, 'commit_creds', '0xc00b14ec');
  INSERT INTO device_address(device_id, name, value) VALUES(89, 'remap_pfn_range', '0xc0135640');
  INSERT INTO device_address(device_id, name, value) VALUES(89, 'ptmx_fops', '0xc0cc37e8');
  INSERT INTO device_address(device_id, name, value) VALUES(89, 'perf_swevent_enabled', '0xc0caf3b4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(90, 'LT26i', '6.2.B.0.211', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(90, 'prepare_kernel_cred', '0xc00b19d8');
  INSERT INTO device_address(device_id, name, value) VALUES(90, 'commit_creds', '0xc00b14fc');
  INSERT INTO device_address(device_id, name, value) VALUES(90, 'remap_pfn_range', '0xc0135650');
  INSERT INTO device_address(device_id, name, value) VALUES(90, 'ptmx_fops', '0xc0cc37e8');
  INSERT INTO device_address(device_id, name, value) VALUES(90, 'perf_swevent_enabled', '0xc0caf3b4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(91, 'LT26i', '6.2.B.1.96', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(91, 'prepare_kernel_cred', '0xc00acc54');
  INSERT INTO device_address(device_id, name, value) VALUES(91, 'commit_creds', '0xc00ac778');
  INSERT INTO device_address(device_id, name, value) VALUES(91, 'remap_pfn_range', '0xc01308d4');
  INSERT INTO device_address(device_id, name, value) VALUES(91, 'vmalloc_exec', '0xc013e640');
  INSERT INTO device_address(device_id, name, value) VALUES(91, 'ptmx_fops', '0xc0cc3788');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(92, 'LT26ii', '6.2.B.0.200', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(92, 'prepare_kernel_cred', '0xc00b19c8');
  INSERT INTO device_address(device_id, name, value) VALUES(92, 'commit_creds', '0xc00b14ec');
  INSERT INTO device_address(device_id, name, value) VALUES(92, 'remap_pfn_range', '0xc0135640');
  INSERT INTO device_address(device_id, name, value) VALUES(92, 'ptmx_fops', '0xc0cc37e8');
  INSERT INTO device_address(device_id, name, value) VALUES(92, 'perf_swevent_enabled', '0xc0caf3b4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(93, 'LT26ii', '6.2.B.0.211', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(93, 'prepare_kernel_cred', '0xc00b19d8');
  INSERT INTO device_address(device_id, name, value) VALUES(93, 'commit_creds', '0xc00b14fc');
  INSERT INTO device_address(device_id, name, value) VALUES(93, 'remap_pfn_range', '0xc0135650');
  INSERT INTO device_address(device_id, name, value) VALUES(93, 'ptmx_fops', '0xc0cc37e8');
  INSERT INTO device_address(device_id, name, value) VALUES(93, 'perf_swevent_enabled', '0xc0caf3b4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(94, 'LT26w', '6.2.B.0.200', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(94, 'prepare_kernel_cred', '0xc00b261c');
  INSERT INTO device_address(device_id, name, value) VALUES(94, 'commit_creds', '0xc00b2140');
  INSERT INTO device_address(device_id, name, value) VALUES(94, 'remap_pfn_range', '0xc0136294');
  INSERT INTO device_address(device_id, name, value) VALUES(94, 'vmalloc_exec', '0xc0143f98');
  INSERT INTO device_address(device_id, name, value) VALUES(94, 'ptmx_fops', '0xc0cc3dc0');
  INSERT INTO device_address(device_id, name, value) VALUES(94, 'perf_swevent_enabled', '0xc0cafa74');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(95, 'LT26w', '6.2.B.0.211', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(95, 'prepare_kernel_cred', '0xc00b262c');
  INSERT INTO device_address(device_id, name, value) VALUES(95, 'commit_creds', '0xc00b2150');
  INSERT INTO device_address(device_id, name, value) VALUES(95, 'remap_pfn_range', '0xc01362a4');
  INSERT INTO device_address(device_id, name, value) VALUES(95, 'ptmx_fops', '0xc0cc3dc0');
  INSERT INTO device_address(device_id, name, value) VALUES(95, 'perf_swevent_enabled', '0xc0cafa74');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(96, 'LT22i', '6.2.A.1.100', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(96, 'prepare_kernel_cred', '0xc00c37c8');
  INSERT INTO device_address(device_id, name, value) VALUES(96, 'commit_creds', '0xc00c33f8');
  INSERT INTO device_address(device_id, name, value) VALUES(96, 'remap_pfn_range', '0xc0136358');
  INSERT INTO device_address(device_id, name, value) VALUES(96, 'ptmx_fops', '0xc09dbed8');
  INSERT INTO device_address(device_id, name, value) VALUES(96, 'perf_swevent_enabled', '0xc09d4110');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(97, 'P-02E', '10.0657', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(97, 'prepare_kernel_cred', '0xc009b868');
  INSERT INTO device_address(device_id, name, value) VALUES(97, 'commit_creds', '0xc009b38c');
  INSERT INTO device_address(device_id, name, value) VALUES(97, 'remap_pfn_range', '0xc0110224');
  INSERT INTO device_address(device_id, name, value) VALUES(97, 'vmalloc_exec', '0xc011c6c8');
  INSERT INTO device_address(device_id, name, value) VALUES(97, 'ptmx_fops', '0xc0f72ba4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(98, 'P-02E', '10.0659', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(98, 'prepare_kernel_cred', '0xc009b868');
  INSERT INTO device_address(device_id, name, value) VALUES(98, 'commit_creds', '0xc009b38c');
  INSERT INTO device_address(device_id, name, value) VALUES(98, 'remap_pfn_range', '0xc0110224');
  INSERT INTO device_address(device_id, name, value) VALUES(98, 'vmalloc_exec', '0xc011c6c8');
  INSERT INTO device_address(device_id, name, value) VALUES(98, 'ptmx_fops', '0xc0f72ba4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(99, 'P-02E', '10.0691', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(99, 'prepare_kernel_cred', '0xc009b868');
  INSERT INTO device_address(device_id, name, value) VALUES(99, 'commit_creds', '0xc009b38c');
  INSERT INTO device_address(device_id, name, value) VALUES(99, 'remap_pfn_range', '0xc0110224');
  INSERT INTO device_address(device_id, name, value) VALUES(99, 'vmalloc_exec', '0xc011c6c8');
  INSERT INTO device_address(device_id, name, value) VALUES(99, 'ptmx_fops', '0xc0f72ba4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(100, 'P-02E', '10.0733', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(100, 'prepare_kernel_cred', '0xc009b878');
  INSERT INTO device_address(device_id, name, value) VALUES(100, 'commit_creds', '0xc009b39c');
  INSERT INTO device_address(device_id, name, value) VALUES(100, 'remap_pfn_range', '0xc0110234');
  INSERT INTO device_address(device_id, name, value) VALUES(100, 'vmalloc_exec', '0xc011c6d8');
  INSERT INTO device_address(device_id, name, value) VALUES(100, 'ptmx_fops', '0xc0f72ba4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(101, 'P-02E', '10.0767', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(101, 'prepare_kernel_cred', '0xc009b888');
  INSERT INTO device_address(device_id, name, value) VALUES(101, 'commit_creds', '0xc009b3ac');
  INSERT INTO device_address(device_id, name, value) VALUES(101, 'remap_pfn_range', '0xc0110244');
  INSERT INTO device_address(device_id, name, value) VALUES(101, 'vmalloc_exec', '0xc011c6e8');
  INSERT INTO device_address(device_id, name, value) VALUES(101, 'ptmx_fops', '0xc0f72be4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(102, 'P-02E', '10.0798', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(102, 'prepare_kernel_cred', '0xc009b93c');
  INSERT INTO device_address(device_id, name, value) VALUES(102, 'commit_creds', '0xc009b460');
  INSERT INTO device_address(device_id, name, value) VALUES(102, 'remap_pfn_range', '0xc0110324');
  INSERT INTO device_address(device_id, name, value) VALUES(102, 'vmalloc_exec', '0xc011c7c8');
  INSERT INTO device_address(device_id, name, value) VALUES(102, 'ptmx_fops', '0xc0f72ba4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(103, 'ST23i', '11.0.A.5.5', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(103, 'prepare_kernel_cred', '0xc00cd94c');
  INSERT INTO device_address(device_id, name, value) VALUES(103, 'commit_creds', '0xc00cda94');
  INSERT INTO device_address(device_id, name, value) VALUES(103, 'remap_pfn_range', '0xc01124bc');
  INSERT INTO device_address(device_id, name, value) VALUES(103, 'ptmx_fops', '0xc095a46c');
  INSERT INTO device_address(device_id, name, value) VALUES(103, 'perf_swevent_enabled', '0xc09500cc');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(104, 'ST23i', '11.0.A.5.8', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(104, 'prepare_kernel_cred', '0xc00cd94c');
  INSERT INTO device_address(device_id, name, value) VALUES(104, 'commit_creds', '0xc00cda94');
  INSERT INTO device_address(device_id, name, value) VALUES(104, 'remap_pfn_range', '0xc01124bc');
  INSERT INTO device_address(device_id, name, value) VALUES(104, 'ptmx_fops', '0xc095846c');
  INSERT INTO device_address(device_id, name, value) VALUES(104, 'perf_swevent_enabled', '0xc094e0cc');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(105, 'ST27i', '6.2.A.1.100', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(105, 'prepare_kernel_cred', '0xc00c314c');
  INSERT INTO device_address(device_id, name, value) VALUES(105, 'commit_creds', '0xc00c2d7c');
  INSERT INTO device_address(device_id, name, value) VALUES(105, 'remap_pfn_range', '0xc01366ec');
  INSERT INTO device_address(device_id, name, value) VALUES(105, 'ptmx_fops', '0xc09b98e0');
  INSERT INTO device_address(device_id, name, value) VALUES(105, 'perf_swevent_enabled', '0xc09b1a70');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(106, 'ST27a', '6.2.A.1.100', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(106, 'prepare_kernel_cred', '0xc00c314c');
  INSERT INTO device_address(device_id, name, value) VALUES(106, 'commit_creds', '0xc00c2d7c');
  INSERT INTO device_address(device_id, name, value) VALUES(106, 'remap_pfn_range', '0xc01366ec');
  INSERT INTO device_address(device_id, name, value) VALUES(106, 'ptmx_fops', '0xc09b98e0');
  INSERT INTO device_address(device_id, name, value) VALUES(106, 'perf_swevent_enabled', '0xc09b1a70');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(107, 'ST26i', '11.2.A.0.21', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(107, 'prepare_kernel_cred', '0xc00af59c');
  INSERT INTO device_address(device_id, name, value) VALUES(107, 'commit_creds', '0xc00af25c');
  INSERT INTO device_address(device_id, name, value) VALUES(107, 'remap_pfn_range', '0xc00fa38c');
  INSERT INTO device_address(device_id, name, value) VALUES(107, 'ptmx_fops', '0xc09b36dc');
  INSERT INTO device_address(device_id, name, value) VALUES(107, 'perf_swevent_enabled', '0xc09ac210');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(108, 'ST26a', '11.2.A.0.21', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(108, 'prepare_kernel_cred', '0xc00af59c');
  INSERT INTO device_address(device_id, name, value) VALUES(108, 'commit_creds', '0xc00af25c');
  INSERT INTO device_address(device_id, name, value) VALUES(108, 'remap_pfn_range', '0xc00fa38c');
  INSERT INTO device_address(device_id, name, value) VALUES(108, 'ptmx_fops', '0xc09b36dc');
  INSERT INTO device_address(device_id, name, value) VALUES(108, 'perf_swevent_enabled', '0xc09ac210');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(109, 'ST26i', '11.2.A.0.31', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(109, 'prepare_kernel_cred', '0xc00af58c');
  INSERT INTO device_address(device_id, name, value) VALUES(109, 'commit_creds', '0xc00af24c');
  INSERT INTO device_address(device_id, name, value) VALUES(109, 'remap_pfn_range', '0xc00fa37c');
  INSERT INTO device_address(device_id, name, value) VALUES(109, 'ptmx_fops', '0xc098365c');
  INSERT INTO device_address(device_id, name, value) VALUES(109, 'perf_swevent_enabled', '0xc097c1d0');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(110, 'ST26a', '11.2.A.0.31', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(110, 'prepare_kernel_cred', '0xc00af58c');
  INSERT INTO device_address(device_id, name, value) VALUES(110, 'commit_creds', '0xc00af24c');
  INSERT INTO device_address(device_id, name, value) VALUES(110, 'remap_pfn_range', '0xc00fa37c');
  INSERT INTO device_address(device_id, name, value) VALUES(110, 'ptmx_fops', '0xc098365c');
  INSERT INTO device_address(device_id, name, value) VALUES(110, 'perf_swevent_enabled', '0xc097c1d0');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(111, 'N-02E', 'A3002501', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(111, 'msm_acdb.value_pos', 148);
  INSERT INTO device_address(device_id, name, value) VALUES(111, 'msm_acdb.address_pos', 164);
  INSERT INTO device_address(device_id, name, value) VALUES(111, 'msm_acdb.pc1.pos', 168);
  INSERT INTO device_address(device_id, name, value) VALUES(111, 'msm_acdb.pc1.value', '0xc0395460');
  INSERT INTO device_address(device_id, name, value) VALUES(111, 'msm_acdb.pc2.pos', 200);
  INSERT INTO device_address(device_id, name, value) VALUES(111, 'msm_acdb.pc2.value', '0xc024a3b4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(112, 'N-02E', 'A3002601', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(112, 'msm_acdb.value_pos', 148);
  INSERT INTO device_address(device_id, name, value) VALUES(112, 'msm_acdb.address_pos', 164);
  INSERT INTO device_address(device_id, name, value) VALUES(112, 'msm_acdb.pc1.pos', 168);
  INSERT INTO device_address(device_id, name, value) VALUES(112, 'msm_acdb.pc1.value', '0xc03953a0');
  INSERT INTO device_address(device_id, name, value) VALUES(112, 'msm_acdb.pc2.pos', 200);
  INSERT INTO device_address(device_id, name, value) VALUES(112, 'msm_acdb.pc2.value', '0xc024a2fc');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(113, 'N-02E', 'A5000331', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(113, 'perf_swevent_enabled', '0xc0f3d3a0');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(114, 'N-02E', 'A5002501', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(114, 'msm_acdb.value_pos', 148);
  INSERT INTO device_address(device_id, name, value) VALUES(114, 'msm_acdb.address_pos', 164);
  INSERT INTO device_address(device_id, name, value) VALUES(114, 'msm_acdb.pc1.pos', 168);
  INSERT INTO device_address(device_id, name, value) VALUES(114, 'msm_acdb.pc1.value', '0xc0395460');
  INSERT INTO device_address(device_id, name, value) VALUES(114, 'msm_acdb.pc2.pos', 200);
  INSERT INTO device_address(device_id, name, value) VALUES(114, 'msm_acdb.pc2.value', '0xc024a3b4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(115, 'N-02E', 'A5002601', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(115, 'msm_acdb.value_pos', 148);
  INSERT INTO device_address(device_id, name, value) VALUES(115, 'msm_acdb.address_pos', 164);
  INSERT INTO device_address(device_id, name, value) VALUES(115, 'msm_acdb.pc1.pos', 168);
  INSERT INTO device_address(device_id, name, value) VALUES(115, 'msm_acdb.pc1.value', '0xc03953a0');
  INSERT INTO device_address(device_id, name, value) VALUES(115, 'msm_acdb.pc2.pos', 200);
  INSERT INTO device_address(device_id, name, value) VALUES(115, 'msm_acdb.pc2.value', '0xc024a2fc');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(116, 'N-03E', 'A7000241', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(116, 'prepare_kernel_cred', '0xc01ab578');
  INSERT INTO device_address(device_id, name, value) VALUES(116, 'commit_creds', '0xc01aadac');
  INSERT INTO device_address(device_id, name, value) VALUES(116, 'remap_pfn_range', '0xc020d990');
  INSERT INTO device_address(device_id, name, value) VALUES(116, 'ptmx_fops', '0xc0f702fc');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(117, 'N-03E', 'A7001821', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(117, 'prepare_kernel_cred', '0xc01ab594');
  INSERT INTO device_address(device_id, name, value) VALUES(117, 'commit_creds', '0xc01aadc8');
  INSERT INTO device_address(device_id, name, value) VALUES(117, 'remap_pfn_range', '0xc020d9ac');
  INSERT INTO device_address(device_id, name, value) VALUES(117, 'ptmx_fops', '0xc0f702fc');
  INSERT INTO device_address(device_id, name, value) VALUES(117, 'perf_swevent_enabled', '0xc0f619c4');
  INSERT INTO device_address(device_id, name, value) VALUES(117, 'msm_acdb.value_pos', 148);
  INSERT INTO device_address(device_id, name, value) VALUES(117, 'msm_acdb.address_pos', 164);
  INSERT INTO device_address(device_id, name, value) VALUES(117, 'msm_acdb.pc1.pos', 168);
  INSERT INTO device_address(device_id, name, value) VALUES(117, 'msm_acdb.pc1.value', '0xc0397cbc');
  INSERT INTO device_address(device_id, name, value) VALUES(117, 'msm_acdb.pc2.pos', 200);
  INSERT INTO device_address(device_id, name, value) VALUES(117, 'msm_acdb.pc2.value', '0xc024ba58');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(118, 'N-03E', 'A7002001', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(118, 'prepare_kernel_cred', '0xc01ab5b8');
  INSERT INTO device_address(device_id, name, value) VALUES(118, 'commit_creds', '0xc01aadec');
  INSERT INTO device_address(device_id, name, value) VALUES(118, 'remap_pfn_range', '0xc020d9f4');
  INSERT INTO device_address(device_id, name, value) VALUES(118, 'ptmx_fops', '0xc0f702fc');
  INSERT INTO device_address(device_id, name, value) VALUES(118, 'msm_acdb.value_pos', 148);
  INSERT INTO device_address(device_id, name, value) VALUES(118, 'msm_acdb.address_pos', 164);
  INSERT INTO device_address(device_id, name, value) VALUES(118, 'msm_acdb.pc1.pos', 168);
  INSERT INTO device_address(device_id, name, value) VALUES(118, 'msm_acdb.pc1.value', '0xc0397ddc');
  INSERT INTO device_address(device_id, name, value) VALUES(118, 'msm_acdb.pc2.pos', 200);
  INSERT INTO device_address(device_id, name, value) VALUES(118, 'msm_acdb.pc2.value', '0xc024bb00');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(119, 'N-03E', 'A7202001', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(119, 'prepare_kernel_cred', '0xc0093760');
  INSERT INTO device_address(device_id, name, value) VALUES(119, 'commit_creds', '0xc00931ec');
  INSERT INTO device_address(device_id, name, value) VALUES(119, 'remap_pfn_range', '0xc0106048');
  INSERT INTO device_address(device_id, name, value) VALUES(119, 'vmalloc_exec', '0xc0112694');
  INSERT INTO device_address(device_id, name, value) VALUES(119, 'ptmx_fops', '0xc0f94d94');
  INSERT INTO device_address(device_id, name, value) VALUES(119, 'msm_acdb.value_pos', 124);
  INSERT INTO device_address(device_id, name, value) VALUES(119, 'msm_acdb.address_pos', 136);
  INSERT INTO device_address(device_id, name, value) VALUES(119, 'msm_acdb.pc1.pos', 140);
  INSERT INTO device_address(device_id, name, value) VALUES(119, 'msm_acdb.pc1.value', '0xc0297e1c');
  INSERT INTO device_address(device_id, name, value) VALUES(119, 'msm_acdb.pc2.pos', 172);
  INSERT INTO device_address(device_id, name, value) VALUES(119, 'msm_acdb.pc2.value', '0xc024be10');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(120, 'N-03E', 'A7202201', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(120, 'prepare_kernel_cred', '0xc0093760');
  INSERT INTO device_address(device_id, name, value) VALUES(120, 'commit_creds', '0xc00931ec');
  INSERT INTO device_address(device_id, name, value) VALUES(120, 'remap_pfn_range', '0xc0106048');
  INSERT INTO device_address(device_id, name, value) VALUES(120, 'vmalloc_exec', '0xc0112694');
  INSERT INTO device_address(device_id, name, value) VALUES(120, 'ptmx_fops', '0xc0f94d94');
  INSERT INTO device_address(device_id, name, value) VALUES(120, 'msm_acdb.value_pos', 124);
  INSERT INTO device_address(device_id, name, value) VALUES(120, 'msm_acdb.address_pos', 136);
  INSERT INTO device_address(device_id, name, value) VALUES(120, 'msm_acdb.pc1.pos', 140);
  INSERT INTO device_address(device_id, name, value) VALUES(120, 'msm_acdb.pc1.value', '0xc0297e1c');
  INSERT INTO device_address(device_id, name, value) VALUES(120, 'msm_acdb.pc2.pos', 172);
  INSERT INTO device_address(device_id, name, value) VALUES(120, 'msm_acdb.pc2.value', '0xc024be10');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(121, 'N05E', 'A1000311', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(121, 'prepare_kernel_cred', '0xc0094430');
  INSERT INTO device_address(device_id, name, value) VALUES(121, 'commit_creds', '0xc0093ebc');
  INSERT INTO device_address(device_id, name, value) VALUES(121, 'remap_pfn_range', '0xc0105800');
  INSERT INTO device_address(device_id, name, value) VALUES(121, 'ptmx_fops', '0xc0f58700');
  INSERT INTO device_address(device_id, name, value) VALUES(121, 'perf_swevent_enabled', '0xc0f408f4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(122, 'SC-01E', 'IMM76D.SC01EOMALJ3', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(122, 'prepare_kernel_cred', '0xc01244b8');
  INSERT INTO device_address(device_id, name, value) VALUES(122, 'commit_creds', '0xc0123d6c');
  INSERT INTO device_address(device_id, name, value) VALUES(122, 'remap_pfn_range', '0xc0192124');
  INSERT INTO device_address(device_id, name, value) VALUES(122, 'ptmx_fops', '0xc10a5a48');
  INSERT INTO device_address(device_id, name, value) VALUES(122, 'delayed_rsp_id', '0xc0bdfae0');
  INSERT INTO device_address(device_id, name, value) VALUES(122, 'perf_swevent_enabled', '0xc1096fc8');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(123, 'SC-01E', 'IMM76D.SC01EOMAMF2', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(123, 'prepare_kernel_cred', '0xc01244d0');
  INSERT INTO device_address(device_id, name, value) VALUES(123, 'commit_creds', '0xc0123d84');
  INSERT INTO device_address(device_id, name, value) VALUES(123, 'remap_pfn_range', '0xc019215c');
  INSERT INTO device_address(device_id, name, value) VALUES(123, 'ptmx_fops', '0xc10a5a48');
  INSERT INTO device_address(device_id, name, value) VALUES(123, 'perf_swevent_enabled', '0xc1096fc8');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(124, 'SC-04E', 'JDQ39.SC04EOMUAMDI', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(124, 'prepare_kernel_cred', '0xc0096068');
  INSERT INTO device_address(device_id, name, value) VALUES(124, 'commit_creds', '0xc0095b54');
  INSERT INTO device_address(device_id, name, value) VALUES(124, 'remap_pfn_range', '0xc011383c');
  INSERT INTO device_address(device_id, name, value) VALUES(124, 'vmalloc_exec', '0xc01206d8');
  INSERT INTO device_address(device_id, name, value) VALUES(124, 'ptmx_fops', '0xc1169808');
  INSERT INTO device_address(device_id, name, value) VALUES(124, 'perf_swevent_enabled', '0xc11489d4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(125, 'SC-04E', 'JDQ39.SC04EOMUAMF1', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(125, 'prepare_kernel_cred', '0xc00960d0');
  INSERT INTO device_address(device_id, name, value) VALUES(125, 'commit_creds', '0xc0095bbc');
  INSERT INTO device_address(device_id, name, value) VALUES(125, 'remap_pfn_range', '0xc01138a4');
  INSERT INTO device_address(device_id, name, value) VALUES(125, 'vmalloc_exec', '0xc0120740');
  INSERT INTO device_address(device_id, name, value) VALUES(125, 'ptmx_fops', '0xc1169848');
  INSERT INTO device_address(device_id, name, value) VALUES(125, 'perf_swevent_enabled', '0xc1148a14');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(126, 'SC-04E', 'JDQ39.SC04EOMUAMF2', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(126, 'prepare_kernel_cred', '0xc00960cc');
  INSERT INTO device_address(device_id, name, value) VALUES(126, 'commit_creds', '0xc0095bb8');
  INSERT INTO device_address(device_id, name, value) VALUES(126, 'remap_pfn_range', '0xc01138a0');
  INSERT INTO device_address(device_id, name, value) VALUES(126, 'vmalloc_exec', '0xc012073c');
  INSERT INTO device_address(device_id, name, value) VALUES(126, 'ptmx_fops', '0xc1169848');
  INSERT INTO device_address(device_id, name, value) VALUES(126, 'perf_swevent_enabled', '0xc1148a14');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(127, 'SC-04E', 'JDQ39.SC04EOMUAMG2', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(127, 'prepare_kernel_cred', '0xc00960cc');
  INSERT INTO device_address(device_id, name, value) VALUES(127, 'commit_creds', '0xc0095bb8');
  INSERT INTO device_address(device_id, name, value) VALUES(127, 'remap_pfn_range', '0xc01138a8');
  INSERT INTO device_address(device_id, name, value) VALUES(127, 'vmalloc_exec', '0xc0120744');
  INSERT INTO device_address(device_id, name, value) VALUES(127, 'ptmx_fops', '0xc1169848');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(128, 'SC-05D', 'IMM76D.OMLPL', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(128, 'delayed_rsp_id', '0xc0cb0924');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(129, 'SCL21', 'IMM76D.SCL21KDALJD', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(129, 'ptmx_fops', '0xc0c71dc0');
  INSERT INTO device_address(device_id, name, value) VALUES(129, 'delayed_rsp_id', '0xc0b96128');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(130, 'SGP321', '10.1.1.A.1.307', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(130, 'prepare_kernel_cred', '0xc0094124');
  INSERT INTO device_address(device_id, name, value) VALUES(130, 'commit_creds', '0xc0093c48');
  INSERT INTO device_address(device_id, name, value) VALUES(130, 'remap_pfn_range', '0xc0109be4');
  INSERT INTO device_address(device_id, name, value) VALUES(130, 'ptmx_fops', '0xc0d36740');
  INSERT INTO device_address(device_id, name, value) VALUES(130, 'perf_swevent_enabled', '0xc0d1f134');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(131, 'SGP312', '10.1.C.0.370', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(131, 'prepare_kernel_cred', '0xc009363c');
  INSERT INTO device_address(device_id, name, value) VALUES(131, 'commit_creds', '0xc0093160');
  INSERT INTO device_address(device_id, name, value) VALUES(131, 'remap_pfn_range', '0xc01090fc');
  INSERT INTO device_address(device_id, name, value) VALUES(131, 'ptmx_fops', '0xc0d35ca8');
  INSERT INTO device_address(device_id, name, value) VALUES(131, 'perf_swevent_enabled', '0xc0d1e6b4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(132, 'SGP311', '10.1.C.0.370', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(132, 'prepare_kernel_cred', '0xc009363c');
  INSERT INTO device_address(device_id, name, value) VALUES(132, 'commit_creds', '0xc0093160');
  INSERT INTO device_address(device_id, name, value) VALUES(132, 'remap_pfn_range', '0xc01090fc');
  INSERT INTO device_address(device_id, name, value) VALUES(132, 'ptmx_fops', '0xc0d35ca8');
  INSERT INTO device_address(device_id, name, value) VALUES(132, 'perf_swevent_enabled', '0xc0d1e6b4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(133, 'LT30p', '9.1.A.1.141', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(133, 'prepare_kernel_cred', '0xc0094878');
  INSERT INTO device_address(device_id, name, value) VALUES(133, 'commit_creds', '0xc009439c');
  INSERT INTO device_address(device_id, name, value) VALUES(133, 'remap_pfn_range', '0xc01096e4');
  INSERT INTO device_address(device_id, name, value) VALUES(133, 'ptmx_fops', '0xc0d02b00');
  INSERT INTO device_address(device_id, name, value) VALUES(133, 'perf_swevent_enabled', '0xc0cedaf4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(134, 'LT30p', '9.1.A.1.142', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(134, 'prepare_kernel_cred', '0xc0094878');
  INSERT INTO device_address(device_id, name, value) VALUES(134, 'commit_creds', '0xc009439c');
  INSERT INTO device_address(device_id, name, value) VALUES(134, 'remap_pfn_range', '0xc01096e4');
  INSERT INTO device_address(device_id, name, value) VALUES(134, 'ptmx_fops', '0xc0d02b00');
  INSERT INTO device_address(device_id, name, value) VALUES(134, 'perf_swevent_enabled', '0xc0cedaf4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(135, 'LT30p', '9.1.A.1.145', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(135, 'prepare_kernel_cred', '0xc0094888');
  INSERT INTO device_address(device_id, name, value) VALUES(135, 'commit_creds', '0xc00943ac');
  INSERT INTO device_address(device_id, name, value) VALUES(135, 'remap_pfn_range', '0xc01096f4');
  INSERT INTO device_address(device_id, name, value) VALUES(135, 'ptmx_fops', '0xc0d02b00');
  INSERT INTO device_address(device_id, name, value) VALUES(135, 'perf_swevent_enabled', '0xc0cedaf4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(136, 'LT29i', '9.1.B.0.411', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(136, 'prepare_kernel_cred', '0xc0095dec');
  INSERT INTO device_address(device_id, name, value) VALUES(136, 'commit_creds', '0xc0095910');
  INSERT INTO device_address(device_id, name, value) VALUES(136, 'remap_pfn_range', '0xc010ac30');
  INSERT INTO device_address(device_id, name, value) VALUES(136, 'vmalloc_exec', '0xc01177e0');
  INSERT INTO device_address(device_id, name, value) VALUES(136, 'ptmx_fops', '0xc0d01f60');
  INSERT INTO device_address(device_id, name, value) VALUES(136, 'perf_swevent_enabled', '0xc0cecd74');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(137, 'LT29i', '9.1.B.1.67', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(137, 'prepare_kernel_cred', '0xc0095ca4');
  INSERT INTO device_address(device_id, name, value) VALUES(137, 'commit_creds', '0xc00957c8');
  INSERT INTO device_address(device_id, name, value) VALUES(137, 'remap_pfn_range', '0xc010aaec');
  INSERT INTO device_address(device_id, name, value) VALUES(137, 'ptmx_fops', '0xc0d01f60');
  INSERT INTO device_address(device_id, name, value) VALUES(137, 'perf_swevent_enabled', '0xc0cecd74');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(138, 'LT25i', '9.1.A.1.140', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(138, 'prepare_kernel_cred', '0xc0097f20');
  INSERT INTO device_address(device_id, name, value) VALUES(138, 'commit_creds', '0xc0097a44');
  INSERT INTO device_address(device_id, name, value) VALUES(138, 'remap_pfn_range', '0xc010dcfc');
  INSERT INTO device_address(device_id, name, value) VALUES(138, 'ptmx_fops', '0xc0d032f8');
  INSERT INTO device_address(device_id, name, value) VALUES(138, 'perf_swevent_enabled', '0xc0cee1f4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(139, 'LT25i', '9.1.A.1.142', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(139, 'prepare_kernel_cred', '0xc0097dd8');
  INSERT INTO device_address(device_id, name, value) VALUES(139, 'commit_creds', '0xc00978fc');
  INSERT INTO device_address(device_id, name, value) VALUES(139, 'remap_pfn_range', '0xc010dbb4');
  INSERT INTO device_address(device_id, name, value) VALUES(139, 'ptmx_fops', '0xc0d032b8');
  INSERT INTO device_address(device_id, name, value) VALUES(139, 'perf_swevent_enabled', '0xc0cee1b4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(140, 'LT25i', '9.1.A.1.145', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(140, 'prepare_kernel_cred', '0xc0097de8');
  INSERT INTO device_address(device_id, name, value) VALUES(140, 'commit_creds', '0xc009790c');
  INSERT INTO device_address(device_id, name, value) VALUES(140, 'remap_pfn_range', '0xc010dbc4');
  INSERT INTO device_address(device_id, name, value) VALUES(140, 'ptmx_fops', '0xc0d032b8');
  INSERT INTO device_address(device_id, name, value) VALUES(140, 'perf_swevent_enabled', '0xc0cee1b4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(141, 'SBM203SH', 'S0024', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(141, 'kernel_physical_offset', '0x80208000');
  INSERT INTO device_address(device_id, name, value) VALUES(141, 'prepare_kernel_cred', '0xc008d5f8');
  INSERT INTO device_address(device_id, name, value) VALUES(141, 'commit_creds', '0xc008d124');
  INSERT INTO device_address(device_id, name, value) VALUES(141, 'remap_pfn_range', '0xc00e4320');
  INSERT INTO device_address(device_id, name, value) VALUES(141, 'vmalloc_exec', '0xc00f0e68');
  INSERT INTO device_address(device_id, name, value) VALUES(141, 'ptmx_fops', '0xc0ef6580');
  INSERT INTO device_address(device_id, name, value) VALUES(141, 'msm_acdb.value_pos', 124);
  INSERT INTO device_address(device_id, name, value) VALUES(141, 'msm_acdb.address_pos', 136);
  INSERT INTO device_address(device_id, name, value) VALUES(141, 'msm_acdb.pc1.pos', 140);
  INSERT INTO device_address(device_id, name, value) VALUES(141, 'msm_acdb.pc1.value', '0xc0247500');
  INSERT INTO device_address(device_id, name, value) VALUES(141, 'msm_acdb.pc2.pos', 172);
  INSERT INTO device_address(device_id, name, value) VALUES(141, 'msm_acdb.pc2.value', '0xc0230ab0');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(142, 'SH-02E', '02.00.02', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(142, 'kernel_physical_offset', '0x80208000');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(143, 'SH-02E', '02.00.03', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(143, 'kernel_physical_offset', '0x80208000');
  INSERT INTO device_address(device_id, name, value) VALUES(143, 'prepare_kernel_cred', '0xc008d60c');
  INSERT INTO device_address(device_id, name, value) VALUES(143, 'commit_creds', '0xc008d138');
  INSERT INTO device_address(device_id, name, value) VALUES(143, 'remap_pfn_range', '0xc00e433c');
  INSERT INTO device_address(device_id, name, value) VALUES(143, 'vmalloc_exec', '0xc00f0e84');
  INSERT INTO device_address(device_id, name, value) VALUES(143, 'ptmx_fops', '0xc0ef62c0');
  INSERT INTO device_address(device_id, name, value) VALUES(143, 'msm_acdb.value_pos', 124);
  INSERT INTO device_address(device_id, name, value) VALUES(143, 'msm_acdb.address_pos', 136);
  INSERT INTO device_address(device_id, name, value) VALUES(143, 'msm_acdb.pc1.pos', 140);
  INSERT INTO device_address(device_id, name, value) VALUES(143, 'msm_acdb.pc1.value', '0xc0247520');
  INSERT INTO device_address(device_id, name, value) VALUES(143, 'msm_acdb.pc2.pos', 172);
  INSERT INTO device_address(device_id, name, value) VALUES(143, 'msm_acdb.pc2.value', '0xc02498d8');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(144, 'SH-04E', '01.00.02', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(144, 'kernel_physical_offset', '0x80208000');
  INSERT INTO device_address(device_id, name, value) VALUES(144, 'prepare_kernel_cred', '0xc008d86c');
  INSERT INTO device_address(device_id, name, value) VALUES(144, 'commit_creds', '0xc008d398');
  INSERT INTO device_address(device_id, name, value) VALUES(144, 'remap_pfn_range', '0xc00e458c');
  INSERT INTO device_address(device_id, name, value) VALUES(144, 'vmalloc_exec', '0xc00f10d4');
  INSERT INTO device_address(device_id, name, value) VALUES(144, 'ptmx_fops', '0xc0eed190');
  INSERT INTO device_address(device_id, name, value) VALUES(144, 'perf_swevent_enabled', '0xc0ed41ec');
  INSERT INTO device_address(device_id, name, value) VALUES(144, 'msm_acdb.value_pos', 124);
  INSERT INTO device_address(device_id, name, value) VALUES(144, 'msm_acdb.address_pos', 136);
  INSERT INTO device_address(device_id, name, value) VALUES(144, 'msm_acdb.pc1.pos', 140);
  INSERT INTO device_address(device_id, name, value) VALUES(144, 'msm_acdb.pc1.value', '0xc02498e0');
  INSERT INTO device_address(device_id, name, value) VALUES(144, 'msm_acdb.pc2.pos', 172);
  INSERT INTO device_address(device_id, name, value) VALUES(144, 'msm_acdb.pc2.value', '0xc000dd1c');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(145, 'SH-04E', '01.00.03', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(145, 'kernel_physical_offset', '0x80208000');
  INSERT INTO device_address(device_id, name, value) VALUES(145, 'prepare_kernel_cred', '0xc008d99c');
  INSERT INTO device_address(device_id, name, value) VALUES(145, 'commit_creds', '0xc008d4c8');
  INSERT INTO device_address(device_id, name, value) VALUES(145, 'remap_pfn_range', '0xc00e46bc');
  INSERT INTO device_address(device_id, name, value) VALUES(145, 'vmalloc_exec', '0xc00f1204');
  INSERT INTO device_address(device_id, name, value) VALUES(145, 'ptmx_fops', '0xc0eed190');
  INSERT INTO device_address(device_id, name, value) VALUES(145, 'perf_swevent_enabled', '0xc0ed41ec');
  INSERT INTO device_address(device_id, name, value) VALUES(145, 'msm_acdb.value_pos', 124);
  INSERT INTO device_address(device_id, name, value) VALUES(145, 'msm_acdb.address_pos', 136);
  INSERT INTO device_address(device_id, name, value) VALUES(145, 'msm_acdb.pc1.pos', 140);
  INSERT INTO device_address(device_id, name, value) VALUES(145, 'msm_acdb.pc1.value', '0xc0249a20');
  INSERT INTO device_address(device_id, name, value) VALUES(145, 'msm_acdb.pc2.pos', 172);
  INSERT INTO device_address(device_id, name, value) VALUES(145, 'msm_acdb.pc2.value', '0xc024bdd8');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(146, 'SH-04E', '01.00.04', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(146, 'kernel_physical_offset', '0x80208000');
  INSERT INTO device_address(device_id, name, value) VALUES(146, 'prepare_kernel_cred', '0xc008d9ac');
  INSERT INTO device_address(device_id, name, value) VALUES(146, 'commit_creds', '0xc008d4d8');
  INSERT INTO device_address(device_id, name, value) VALUES(146, 'remap_pfn_range', '0xc00e46d4');
  INSERT INTO device_address(device_id, name, value) VALUES(146, 'vmalloc_exec', '0xc00f121c');
  INSERT INTO device_address(device_id, name, value) VALUES(146, 'ptmx_fops', '0xc0eed150');
  INSERT INTO device_address(device_id, name, value) VALUES(146, 'msm_acdb.value_pos', 124);
  INSERT INTO device_address(device_id, name, value) VALUES(146, 'msm_acdb.address_pos', 136);
  INSERT INTO device_address(device_id, name, value) VALUES(146, 'msm_acdb.pc1.pos', 140);
  INSERT INTO device_address(device_id, name, value) VALUES(146, 'msm_acdb.pc1.value', '0xc0249a20');
  INSERT INTO device_address(device_id, name, value) VALUES(146, 'msm_acdb.pc2.pos', 172);
  INSERT INTO device_address(device_id, name, value) VALUES(146, 'msm_acdb.pc2.value', '0xc024bdd8');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(147, 'SH-05E', '01.00.05', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(147, 'kernel_physical_offset', '0x80208000');
  INSERT INTO device_address(device_id, name, value) VALUES(147, 'prepare_kernel_cred', '0xc01932f4');
  INSERT INTO device_address(device_id, name, value) VALUES(147, 'commit_creds', '0xc0192ba8');
  INSERT INTO device_address(device_id, name, value) VALUES(147, 'remap_pfn_range', '0xc01f29c0');
  INSERT INTO device_address(device_id, name, value) VALUES(147, 'vmalloc_exec', '0xc01fd520');
  INSERT INTO device_address(device_id, name, value) VALUES(147, 'ptmx_fops', '0xc0d95870');
  INSERT INTO device_address(device_id, name, value) VALUES(147, 'msm_acdb.value_pos', 128);
  INSERT INTO device_address(device_id, name, value) VALUES(147, 'msm_acdb.address_pos', 144);
  INSERT INTO device_address(device_id, name, value) VALUES(147, 'msm_acdb.pc1.pos', 156);
  INSERT INTO device_address(device_id, name, value) VALUES(147, 'msm_acdb.pc1.value', '0xc0381b98');
  INSERT INTO device_address(device_id, name, value) VALUES(147, 'msm_acdb.pc2.pos', 188);
  INSERT INTO device_address(device_id, name, value) VALUES(147, 'msm_acdb.pc2.value', '0xc0231b98');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(148, 'SH-05E', '01.00.06', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(148, 'kernel_physical_offset', '0x80208000');
  INSERT INTO device_address(device_id, name, value) VALUES(148, 'prepare_kernel_cred', '0xc019330c');
  INSERT INTO device_address(device_id, name, value) VALUES(148, 'commit_creds', '0xc0192bc0');
  INSERT INTO device_address(device_id, name, value) VALUES(148, 'remap_pfn_range', '0xc01f29fc');
  INSERT INTO device_address(device_id, name, value) VALUES(148, 'vmalloc_exec', '0xc01fd55c');
  INSERT INTO device_address(device_id, name, value) VALUES(148, 'ptmx_fops', '0xc0d95870');
  INSERT INTO device_address(device_id, name, value) VALUES(148, 'msm_acdb.value_pos', 128);
  INSERT INTO device_address(device_id, name, value) VALUES(148, 'msm_acdb.address_pos', 144);
  INSERT INTO device_address(device_id, name, value) VALUES(148, 'msm_acdb.pc1.pos', 156);
  INSERT INTO device_address(device_id, name, value) VALUES(148, 'msm_acdb.pc1.value', '0xc0381c58');
  INSERT INTO device_address(device_id, name, value) VALUES(148, 'msm_acdb.pc2.pos', 188);
  INSERT INTO device_address(device_id, name, value) VALUES(148, 'msm_acdb.pc2.value', '0xc0231bd4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(149, 'SH-06E', '01.00.01', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(149, 'kernel_physical_offset', '0x80208000');
  INSERT INTO device_address(device_id, name, value) VALUES(149, 'prepare_kernel_cred', '0xc0099c08');
  INSERT INTO device_address(device_id, name, value) VALUES(149, 'commit_creds', '0xc0099734');
  INSERT INTO device_address(device_id, name, value) VALUES(149, 'remap_pfn_range', '0xc010d5f8');
  INSERT INTO device_address(device_id, name, value) VALUES(149, 'vmalloc_exec', '0xc011a190');
  INSERT INTO device_address(device_id, name, value) VALUES(149, 'ptmx_fops', '0xc104e6c8');
  INSERT INTO device_address(device_id, name, value) VALUES(149, 'msm_acdb.value_pos', 124);
  INSERT INTO device_address(device_id, name, value) VALUES(149, 'msm_acdb.address_pos', 136);
  INSERT INTO device_address(device_id, name, value) VALUES(149, 'msm_acdb.pc1.pos', 140);
  INSERT INTO device_address(device_id, name, value) VALUES(149, 'msm_acdb.pc1.value', '0xc02944b4');
  INSERT INTO device_address(device_id, name, value) VALUES(149, 'msm_acdb.pc2.pos', 172);
  INSERT INTO device_address(device_id, name, value) VALUES(149, 'msm_acdb.pc2.value', '0xc000ddac');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(150, 'SH-06E', '01.00.05', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(150, 'kernel_physical_offset', '0x80208000');
  INSERT INTO device_address(device_id, name, value) VALUES(150, 'prepare_kernel_cred', '0xc0099be0');
  INSERT INTO device_address(device_id, name, value) VALUES(150, 'commit_creds', '0xc009970c');
  INSERT INTO device_address(device_id, name, value) VALUES(150, 'remap_pfn_range', '0xc010d5d8');
  INSERT INTO device_address(device_id, name, value) VALUES(150, 'vmalloc_exec', '0xc011a170');
  INSERT INTO device_address(device_id, name, value) VALUES(150, 'ptmx_fops', '0xc104f1c8');
  INSERT INTO device_address(device_id, name, value) VALUES(150, 'msm_acdb.value_pos', 124);
  INSERT INTO device_address(device_id, name, value) VALUES(150, 'msm_acdb.address_pos', 136);
  INSERT INTO device_address(device_id, name, value) VALUES(150, 'msm_acdb.pc1.pos', 140);
  INSERT INTO device_address(device_id, name, value) VALUES(150, 'msm_acdb.pc1.value', '0xc0294494');
  INSERT INTO device_address(device_id, name, value) VALUES(150, 'msm_acdb.pc2.pos', 172);
  INSERT INTO device_address(device_id, name, value) VALUES(150, 'msm_acdb.pc2.value', '0xc000ddac');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(151, 'SH-06E', '01.00.06', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(151, 'kernel_physical_offset', '0x80208000');
  INSERT INTO device_address(device_id, name, value) VALUES(151, 'prepare_kernel_cred', '0xc0099bf0');
  INSERT INTO device_address(device_id, name, value) VALUES(151, 'commit_creds', '0xc009971c');
  INSERT INTO device_address(device_id, name, value) VALUES(151, 'remap_pfn_range', '0xc010d5e8');
  INSERT INTO device_address(device_id, name, value) VALUES(151, 'vmalloc_exec', '0xc011a180');
  INSERT INTO device_address(device_id, name, value) VALUES(151, 'ptmx_fops', '0xc1050090');
  INSERT INTO device_address(device_id, name, value) VALUES(151, 'msm_acdb.value_pos', 124);
  INSERT INTO device_address(device_id, name, value) VALUES(151, 'msm_acdb.address_pos', 136);
  INSERT INTO device_address(device_id, name, value) VALUES(151, 'msm_acdb.pc1.pos', 140);
  INSERT INTO device_address(device_id, name, value) VALUES(151, 'msm_acdb.pc1.value', '0xc02944b4');
  INSERT INTO device_address(device_id, name, value) VALUES(151, 'msm_acdb.pc2.pos', 172);
  INSERT INTO device_address(device_id, name, value) VALUES(151, 'msm_acdb.pc2.value', '0xc000ddac');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(152, 'SH-06E', '01.00.07', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(152, 'kernel_physical_offset', '0x80208000');
  INSERT INTO device_address(device_id, name, value) VALUES(152, 'prepare_kernel_cred', '0xc0099bdc');
  INSERT INTO device_address(device_id, name, value) VALUES(152, 'commit_creds', '0xc0099708');
  INSERT INTO device_address(device_id, name, value) VALUES(152, 'remap_pfn_range', '0xc010d5d4');
  INSERT INTO device_address(device_id, name, value) VALUES(152, 'vmalloc_exec', '0xc011a1d4');
  INSERT INTO device_address(device_id, name, value) VALUES(152, 'ptmx_fops', '0xc1050090');
  INSERT INTO device_address(device_id, name, value) VALUES(152, 'msm_acdb.value_pos', 124);
  INSERT INTO device_address(device_id, name, value) VALUES(152, 'msm_acdb.address_pos', 136);
  INSERT INTO device_address(device_id, name, value) VALUES(152, 'msm_acdb.pc1.pos', 140);
  INSERT INTO device_address(device_id, name, value) VALUES(152, 'msm_acdb.pc1.value', '0xc02944f4');
  INSERT INTO device_address(device_id, name, value) VALUES(152, 'msm_acdb.pc2.pos', 172);
  INSERT INTO device_address(device_id, name, value) VALUES(152, 'msm_acdb.pc2.value', '0xc000ddac');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(153, 'SH-07E', '01.00.03', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(153, 'kernel_physical_offset', '0x80208000');
  INSERT INTO device_address(device_id, name, value) VALUES(153, 'prepare_kernel_cred', '0xc0099e0c');
  INSERT INTO device_address(device_id, name, value) VALUES(153, 'commit_creds', '0xc0099938');
  INSERT INTO device_address(device_id, name, value) VALUES(153, 'remap_pfn_range', '0xc010d804');
  INSERT INTO device_address(device_id, name, value) VALUES(153, 'vmalloc_exec', '0xc011a39c');
  INSERT INTO device_address(device_id, name, value) VALUES(153, 'ptmx_fops', '0xc0f33508');
  INSERT INTO device_address(device_id, name, value) VALUES(153, 'msm_acdb.value_pos', 124);
  INSERT INTO device_address(device_id, name, value) VALUES(153, 'msm_acdb.address_pos', 136);
  INSERT INTO device_address(device_id, name, value) VALUES(153, 'msm_acdb.pc1.pos', 140);
  INSERT INTO device_address(device_id, name, value) VALUES(153, 'msm_acdb.pc1.value', '0xc02946d4');
  INSERT INTO device_address(device_id, name, value) VALUES(153, 'msm_acdb.pc2.pos', 172);
  INSERT INTO device_address(device_id, name, value) VALUES(153, 'msm_acdb.pc2.value', '0xc022729c');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(154, 'SH-09D', '02.00.03', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(154, 'kernel_physical_offset', '0x80208000');
  INSERT INTO device_address(device_id, name, value) VALUES(154, 'prepare_kernel_cred', '0xc008bab4');
  INSERT INTO device_address(device_id, name, value) VALUES(154, 'commit_creds', '0xc008b5e0');
  INSERT INTO device_address(device_id, name, value) VALUES(154, 'remap_pfn_range', '0xc00e25e0');
  INSERT INTO device_address(device_id, name, value) VALUES(154, 'vmalloc_exec', '0xc00ef128');
  INSERT INTO device_address(device_id, name, value) VALUES(154, 'ptmx_fops', '0xc0dd5e58');
  INSERT INTO device_address(device_id, name, value) VALUES(154, 'msm_acdb.value_pos', 124);
  INSERT INTO device_address(device_id, name, value) VALUES(154, 'msm_acdb.address_pos', 136);
  INSERT INTO device_address(device_id, name, value) VALUES(154, 'msm_acdb.pc1.pos', 140);
  INSERT INTO device_address(device_id, name, value) VALUES(154, 'msm_acdb.pc1.value', '0xc0245740');
  INSERT INTO device_address(device_id, name, value) VALUES(154, 'msm_acdb.pc2.pos', 172);
  INSERT INTO device_address(device_id, name, value) VALUES(154, 'msm_acdb.pc2.value', '0xc0238d14');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(155, 'SHL21', '01.00.09', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(155, 'kernel_physical_offset', '0x80208000');
  INSERT INTO device_address(device_id, name, value) VALUES(155, 'prepare_kernel_cred', '0xc0197b94');
  INSERT INTO device_address(device_id, name, value) VALUES(155, 'commit_creds', '0xc0197448');
  INSERT INTO device_address(device_id, name, value) VALUES(155, 'remap_pfn_range', '0xc01f18d0');
  INSERT INTO device_address(device_id, name, value) VALUES(155, 'vmalloc_exec', '0xc01fc498');
  INSERT INTO device_address(device_id, name, value) VALUES(155, 'ptmx_fops', '0xc0fe01b0');
  INSERT INTO device_address(device_id, name, value) VALUES(155, 'msm_acdb.value_pos', 124);
  INSERT INTO device_address(device_id, name, value) VALUES(155, 'msm_acdb.address_pos', 140);
  INSERT INTO device_address(device_id, name, value) VALUES(155, 'msm_acdb.pc1.pos', 144);
  INSERT INTO device_address(device_id, name, value) VALUES(155, 'msm_acdb.pc1.value', '0xc0380240');
  INSERT INTO device_address(device_id, name, value) VALUES(155, 'msm_acdb.pc2.pos', 176);
  INSERT INTO device_address(device_id, name, value) VALUES(155, 'msm_acdb.pc2.value', '0xc02304a8');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(156, 'SHL21', '01.01.02', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(156, 'kernel_physical_offset', '0x80208000');
  INSERT INTO device_address(device_id, name, value) VALUES(156, 'prepare_kernel_cred', '0xc008be38');
  INSERT INTO device_address(device_id, name, value) VALUES(156, 'commit_creds', '0xc008b964');
  INSERT INTO device_address(device_id, name, value) VALUES(156, 'remap_pfn_range', '0xc00e29e0');
  INSERT INTO device_address(device_id, name, value) VALUES(156, 'vmalloc_exec', '0xc00ef528');
  INSERT INTO device_address(device_id, name, value) VALUES(156, 'ptmx_fops', '0xc0dd8810');
  INSERT INTO device_address(device_id, name, value) VALUES(156, 'perf_swevent_enabled', '0xc0dbc96c');
  INSERT INTO device_address(device_id, name, value) VALUES(156, 'msm_acdb.value_pos', 124);
  INSERT INTO device_address(device_id, name, value) VALUES(156, 'msm_acdb.address_pos', 136);
  INSERT INTO device_address(device_id, name, value) VALUES(156, 'msm_acdb.pc1.pos', 140);
  INSERT INTO device_address(device_id, name, value) VALUES(156, 'msm_acdb.pc1.value', '0xc0246100');
  INSERT INTO device_address(device_id, name, value) VALUES(156, 'msm_acdb.pc2.pos', 172);
  INSERT INTO device_address(device_id, name, value) VALUES(156, 'msm_acdb.pc2.value', '0xc02484b8');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(157, 'SO-01E', '9.1.C.0.473', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(157, 'prepare_kernel_cred', '0xc009843c');
  INSERT INTO device_address(device_id, name, value) VALUES(157, 'commit_creds', '0xc0097f60');
  INSERT INTO device_address(device_id, name, value) VALUES(157, 'remap_pfn_range', '0xc010e1f4');
  INSERT INTO device_address(device_id, name, value) VALUES(157, 'ptmx_fops', '0xc0d03208');
  INSERT INTO device_address(device_id, name, value) VALUES(157, 'perf_swevent_enabled', '0xc0cee0f4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(158, 'SO-01E', '9.1.C.1.103', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(158, 'prepare_kernel_cred', '0xc009844c');
  INSERT INTO device_address(device_id, name, value) VALUES(158, 'commit_creds', '0xc0097f70');
  INSERT INTO device_address(device_id, name, value) VALUES(158, 'remap_pfn_range', '0xc010e238');
  INSERT INTO device_address(device_id, name, value) VALUES(158, 'ptmx_fops', '0xc0d03288');
  INSERT INTO device_address(device_id, name, value) VALUES(158, 'perf_swevent_enabled', '0xc0cee174');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(159, 'SO-02E', '10.1.D.0.343', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(159, 'prepare_kernel_cred', '0xc009ca34');
  INSERT INTO device_address(device_id, name, value) VALUES(159, 'commit_creds', '0xc009c558');
  INSERT INTO device_address(device_id, name, value) VALUES(159, 'remap_pfn_range', '0xc01124f4');
  INSERT INTO device_address(device_id, name, value) VALUES(159, 'ptmx_fops', '0xc0e38620');
  INSERT INTO device_address(device_id, name, value) VALUES(159, 'perf_swevent_enabled', '0xc0e20d74');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(160, 'SO-03E', '10.1.E.0.265', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(160, 'prepare_kernel_cred', '0xc00938a0');
  INSERT INTO device_address(device_id, name, value) VALUES(160, 'commit_creds', '0xc00933c4');
  INSERT INTO device_address(device_id, name, value) VALUES(160, 'remap_pfn_range', '0xc0109360');
  INSERT INTO device_address(device_id, name, value) VALUES(160, 'ptmx_fops', '0xc0d36aa8');
  INSERT INTO device_address(device_id, name, value) VALUES(160, 'perf_swevent_enabled', '0xc0d1f4b4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(161, 'SO-03E', '10.1.E.0.269', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(161, 'prepare_kernel_cred', '0xc00938b0');
  INSERT INTO device_address(device_id, name, value) VALUES(161, 'commit_creds', '0xc00933d4');
  INSERT INTO device_address(device_id, name, value) VALUES(161, 'remap_pfn_range', '0xc0109370');
  INSERT INTO device_address(device_id, name, value) VALUES(161, 'ptmx_fops', '0xc0d36aa8');
  INSERT INTO device_address(device_id, name, value) VALUES(161, 'perf_swevent_enabled', '0xc0d1f4b4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(162, 'SO-04D', '7.0.D.1.137', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(162, 'ptmx_fops', '0xc0c9d8a0');
  INSERT INTO device_address(device_id, name, value) VALUES(162, 'perf_swevent_enabled', '0xc0c91ea0');
  INSERT INTO device_address(device_id, name, value) VALUES(162, 'msm_acdb.value_pos', 128);
  INSERT INTO device_address(device_id, name, value) VALUES(162, 'msm_acdb.address_pos', 144);
  INSERT INTO device_address(device_id, name, value) VALUES(162, 'msm_acdb.pc1.pos', 156);
  INSERT INTO device_address(device_id, name, value) VALUES(162, 'msm_acdb.pc1.value', '0xc0326a38');
  INSERT INTO device_address(device_id, name, value) VALUES(162, 'msm_acdb.pc2.pos', 188);
  INSERT INTO device_address(device_id, name, value) VALUES(162, 'msm_acdb.pc2.value', '0xc0526964');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(163, 'SO-04D', '9.1.C.0.475', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(163, 'prepare_kernel_cred', '0xc0095cb0');
  INSERT INTO device_address(device_id, name, value) VALUES(163, 'commit_creds', '0xc00957d4');
  INSERT INTO device_address(device_id, name, value) VALUES(163, 'remap_pfn_range', '0xc010aaf8');
  INSERT INTO device_address(device_id, name, value) VALUES(163, 'ptmx_fops', '0xc0d024a0');
  INSERT INTO device_address(device_id, name, value) VALUES(163, 'perf_swevent_enabled', '0xc0ced2b4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(164, 'SO-04D', '9.1.C.1.103', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(164, 'prepare_kernel_cred', '0xc0095cc0');
  INSERT INTO device_address(device_id, name, value) VALUES(164, 'commit_creds', '0xc00957e4');
  INSERT INTO device_address(device_id, name, value) VALUES(164, 'remap_pfn_range', '0xc010ab3c');
  INSERT INTO device_address(device_id, name, value) VALUES(164, 'ptmx_fops', '0xc0d024a0');
  INSERT INTO device_address(device_id, name, value) VALUES(164, 'perf_swevent_enabled', '0xc0ced2b4');
  INSERT INTO device_address(device_id, name, value) VALUES(164, 'msm_acdb.value_pos', 124);
  INSERT INTO device_address(device_id, name, value) VALUES(164, 'msm_acdb.address_pos', 136);
  INSERT INTO device_address(device_id, name, value) VALUES(164, 'msm_acdb.pc1.pos', 140);
  INSERT INTO device_address(device_id, name, value) VALUES(164, 'msm_acdb.pc1.value', '0xc0240958');
  INSERT INTO device_address(device_id, name, value) VALUES(164, 'msm_acdb.pc2.pos', 172);
  INSERT INTO device_address(device_id, name, value) VALUES(164, 'msm_acdb.pc2.value', '0xc003dfd0');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(165, 'SO-04E', '10.1.1.D.0.179', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(165, 'prepare_kernel_cred', '0xc009d500');
  INSERT INTO device_address(device_id, name, value) VALUES(165, 'commit_creds', '0xc009d024');
  INSERT INTO device_address(device_id, name, value) VALUES(165, 'remap_pfn_range', '0xc0112fc0');
  INSERT INTO device_address(device_id, name, value) VALUES(165, 'ptmx_fops', '0xc0f392d8');
  INSERT INTO device_address(device_id, name, value) VALUES(165, 'perf_swevent_enabled', '0xc0f21af4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(166, 'SO-04E', '10.1.1.D.2.26', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(166, 'prepare_kernel_cred', '0xc009d510');
  INSERT INTO device_address(device_id, name, value) VALUES(166, 'commit_creds', '0xc009d034');
  INSERT INTO device_address(device_id, name, value) VALUES(166, 'remap_pfn_range', '0xc0112fd0');
  INSERT INTO device_address(device_id, name, value) VALUES(166, 'ptmx_fops', '0xc0f392d8');
  INSERT INTO device_address(device_id, name, value) VALUES(166, 'perf_swevent_enabled', '0xc0f21af4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(167, 'SO-05D', '7.0.D.1.117', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(167, 'delayed_rsp_id', '0xc0b8840c');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(168, 'SO-05D', '7.0.D.1.137', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(168, 'msm_acdb.value_pos', 128);
  INSERT INTO device_address(device_id, name, value) VALUES(168, 'msm_acdb.address_pos', 144);
  INSERT INTO device_address(device_id, name, value) VALUES(168, 'msm_acdb.pc1.pos', 156);
  INSERT INTO device_address(device_id, name, value) VALUES(168, 'msm_acdb.pc1.value', '0xc03265d8');
  INSERT INTO device_address(device_id, name, value) VALUES(168, 'msm_acdb.pc2.pos', 188);
  INSERT INTO device_address(device_id, name, value) VALUES(168, 'msm_acdb.pc2.value', '0xc0524d84');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(169, 'SO-05D', '9.1.C.0.475', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(169, 'prepare_kernel_cred', '0xc00958ac');
  INSERT INTO device_address(device_id, name, value) VALUES(169, 'commit_creds', '0xc00953d0');
  INSERT INTO device_address(device_id, name, value) VALUES(169, 'remap_pfn_range', '0xc010a6f4');
  INSERT INTO device_address(device_id, name, value) VALUES(169, 'ptmx_fops', '0xc0d01e50');
  INSERT INTO device_address(device_id, name, value) VALUES(169, 'perf_swevent_enabled', '0xc0cece34');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(170, 'SO-05D', '9.1.C.1.103', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(170, 'prepare_kernel_cred', '0xc00958bc');
  INSERT INTO device_address(device_id, name, value) VALUES(170, 'commit_creds', '0xc00953e0');
  INSERT INTO device_address(device_id, name, value) VALUES(170, 'remap_pfn_range', '0xc010a738');
  INSERT INTO device_address(device_id, name, value) VALUES(170, 'ptmx_fops', '0xc0d01e90');
  INSERT INTO device_address(device_id, name, value) VALUES(170, 'perf_swevent_enabled', '0xc0cece74');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(171, 'SOL21', '9.0.F.0.226', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(171, 'ptmx_fops', '0xc0cffe78');
  INSERT INTO device_address(device_id, name, value) VALUES(171, 'perf_swevent_enabled', '0xc0cf3360');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(172, 'SOL21', '9.1.D.0.395', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(172, 'prepare_kernel_cred', '0xc0098584');
  INSERT INTO device_address(device_id, name, value) VALUES(172, 'commit_creds', '0xc00980a8');
  INSERT INTO device_address(device_id, name, value) VALUES(172, 'remap_pfn_range', '0xc010e33c');
  INSERT INTO device_address(device_id, name, value) VALUES(172, 'vmalloc_exec', '0xc011aeec');
  INSERT INTO device_address(device_id, name, value) VALUES(172, 'ptmx_fops', '0xc0d030c8');
  INSERT INTO device_address(device_id, name, value) VALUES(172, 'perf_swevent_enabled', '0xc0cedfb4');
  INSERT INTO device_address(device_id, name, value) VALUES(172, 'msm_acdb.value_pos', 124);
  INSERT INTO device_address(device_id, name, value) VALUES(172, 'msm_acdb.address_pos', 136);
  INSERT INTO device_address(device_id, name, value) VALUES(172, 'msm_acdb.pc1.pos', 140);
  INSERT INTO device_address(device_id, name, value) VALUES(172, 'msm_acdb.pc1.value', '0xc0244778');
  INSERT INTO device_address(device_id, name, value) VALUES(172, 'msm_acdb.pc2.pos', 172);
  INSERT INTO device_address(device_id, name, value) VALUES(172, 'msm_acdb.pc2.value', '0xc000dd24');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(173, 'SOL21', '9.1.D.0.401', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(173, 'prepare_kernel_cred', '0xc0098594');
  INSERT INTO device_address(device_id, name, value) VALUES(173, 'commit_creds', '0xc00980b8');
  INSERT INTO device_address(device_id, name, value) VALUES(173, 'remap_pfn_range', '0xc010e34c');
  INSERT INTO device_address(device_id, name, value) VALUES(173, 'ptmx_fops', '0xc0d030c8');
  INSERT INTO device_address(device_id, name, value) VALUES(173, 'perf_swevent_enabled', '0xc0cedfb4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(174, 'SOL22', '10.2.F.3.43', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(174, 'prepare_kernel_cred', '0xc009d3f8');
  INSERT INTO device_address(device_id, name, value) VALUES(174, 'commit_creds', '0xc009cf1c');
  INSERT INTO device_address(device_id, name, value) VALUES(174, 'remap_pfn_range', '0xc0112230');
  INSERT INTO device_address(device_id, name, value) VALUES(174, 'ptmx_fops', '0xc0e389b0');
  INSERT INTO device_address(device_id, name, value) VALUES(174, 'perf_swevent_enabled', '0xc0e20ff4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(175, 'SOL22', '10.2.F.3.81', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(175, 'prepare_kernel_cred', '0xc009d408');
  INSERT INTO device_address(device_id, name, value) VALUES(175, 'commit_creds', '0xc009cf2c');
  INSERT INTO device_address(device_id, name, value) VALUES(175, 'remap_pfn_range', '0xc0112248');
  INSERT INTO device_address(device_id, name, value) VALUES(175, 'vmalloc_exec', '0xc011ee78');
  INSERT INTO device_address(device_id, name, value) VALUES(175, 'ptmx_fops', '0xc0e389b0');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(176, 'Sony Tablet P', 'TISU0144', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(176, 'ptmx_fops', '0xc06e6da0');
  INSERT INTO device_address(device_id, name, value) VALUES(176, 'perf_swevent_enabled', '0xc06dd794');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(177, 'Sony Tablet S', 'TISU0143', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(177, 'ptmx_fops', '0xc06e4d18');
  INSERT INTO device_address(device_id, name, value) VALUES(177, 'perf_swevent_enabled', '0xc06db714');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(178, 'T-02D', 'V10R36A', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(178, 'prepare_kernel_cred', '0xc009c72c');
  INSERT INTO device_address(device_id, name, value) VALUES(178, 'commit_creds', '0xc009c1b4');
  INSERT INTO device_address(device_id, name, value) VALUES(178, 'remap_pfn_range', '0xc0115e48');
  INSERT INTO device_address(device_id, name, value) VALUES(178, 'vmalloc_exec', '0xc0122e08');
  INSERT INTO device_address(device_id, name, value) VALUES(178, 'ptmx_fops', '0xc121b61c');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(179, 'Nexus 4', 'JDQ39', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(179, 'prepare_kernel_cred', '0xc0089990');
  INSERT INTO device_address(device_id, name, value) VALUES(179, 'commit_creds', '0xc0089678');
  INSERT INTO device_address(device_id, name, value) VALUES(179, 'remap_pfn_range', '0xc00f8114');
  INSERT INTO device_address(device_id, name, value) VALUES(179, 'ptmx_fops', '0xc0ef72f0');
  INSERT INTO device_address(device_id, name, value) VALUES(179, 'perf_swevent_enabled', '0xc0ee0070');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(180, 'Galaxy Nexus', 'JOP40C', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(180, 'prepare_kernel_cred', '0xc00cdef0');
  INSERT INTO device_address(device_id, name, value) VALUES(180, 'commit_creds', '0xc00cdbb8');
  INSERT INTO device_address(device_id, name, value) VALUES(180, 'remap_pfn_range', '0xc01350b0');
  INSERT INTO device_address(device_id, name, value) VALUES(180, 'ptmx_fops', '0xc08b5344');
  INSERT INTO device_address(device_id, name, value) VALUES(180, 'perf_swevent_enabled', '0xc089b280');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(181, 'NEC-101T', '112.55.12.2.02.01', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(181, 'prepare_kernel_cred', '0xc00fa134');
  INSERT INTO device_address(device_id, name, value) VALUES(181, 'commit_creds', '0xc00fa28c');
  INSERT INTO device_address(device_id, name, value) VALUES(181, 'remap_pfn_range', '0xc013cccc');
  INSERT INTO device_address(device_id, name, value) VALUES(181, 'ptmx_fops', '0xc02c6da8');
  INSERT INTO device_address(device_id, name, value) VALUES(181, 'perf_swevent_enabled', '0xc011e8b8');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(182, 'Galaxy Nexus', 'JZO54K', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(182, 'prepare_kernel_cred', '0xc00cdee0');
  INSERT INTO device_address(device_id, name, value) VALUES(182, 'commit_creds', '0xc00cdba8');
  INSERT INTO device_address(device_id, name, value) VALUES(182, 'remap_pfn_range', '0xc013509c');
  INSERT INTO device_address(device_id, name, value) VALUES(182, 'ptmx_fops', '0xc08b3224');
  INSERT INTO device_address(device_id, name, value) VALUES(182, 'perf_swevent_enabled', '0xc0899160');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(183, 'C5503', '10.1.1.A.1.310', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(183, 'prepare_kernel_cred', '0xc0093cd8');
  INSERT INTO device_address(device_id, name, value) VALUES(183, 'commit_creds', '0xc00937fc');
  INSERT INTO device_address(device_id, name, value) VALUES(183, 'remap_pfn_range', '0xc0109798');
  INSERT INTO device_address(device_id, name, value) VALUES(183, 'ptmx_fops', '0xc0d37a98');
  INSERT INTO device_address(device_id, name, value) VALUES(183, 'perf_swevent_enabled', '0xc0d202b4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(184, 'C5502', '10.1.1.A.1.310', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(184, 'prepare_kernel_cred', '0xc0093cd8');
  INSERT INTO device_address(device_id, name, value) VALUES(184, 'commit_creds', '0xc00937fc');
  INSERT INTO device_address(device_id, name, value) VALUES(184, 'remap_pfn_range', '0xc0109798');
  INSERT INTO device_address(device_id, name, value) VALUES(184, 'ptmx_fops', '0xc0d37a98');
  INSERT INTO device_address(device_id, name, value) VALUES(184, 'perf_swevent_enabled', '0xc0d202b4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(185, 'M36h', '10.1.1.A.1.310', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(185, 'prepare_kernel_cred', '0xc0093cd8');
  INSERT INTO device_address(device_id, name, value) VALUES(185, 'commit_creds', '0xc00937fc');
  INSERT INTO device_address(device_id, name, value) VALUES(185, 'remap_pfn_range', '0xc0109798');
  INSERT INTO device_address(device_id, name, value) VALUES(185, 'ptmx_fops', '0xc0d37a98');
  INSERT INTO device_address(device_id, name, value) VALUES(185, 'perf_swevent_enabled', '0xc0d202b4');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(186, 'ASUS Pad TF300T', 'JRO03C.JP_epad-10.4.2.20-20121228', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(186, 'prepare_kernel_cred', '0xc0095f0c');
  INSERT INTO device_address(device_id, name, value) VALUES(186, 'commit_creds', '0xc0095bd8');
  INSERT INTO device_address(device_id, name, value) VALUES(186, 'remap_pfn_range', '0xc0100f68');
  INSERT INTO device_address(device_id, name, value) VALUES(186, 'ptmx_fops', '0xc0a706d8');
  INSERT INTO device_address(device_id, name, value) VALUES(186, 'perf_swevent_enabled', '0xc0a67914');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(187, 'SCH-I545', 'JDQ39.I545VRUAME7', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(187, 'prepare_kernel_cred', '0xc0095d1c');
  INSERT INTO device_address(device_id, name, value) VALUES(187, 'commit_creds', '0xc0095808');
  INSERT INTO device_address(device_id, name, value) VALUES(187, 'remap_pfn_range', '0xc011358c');
  INSERT INTO device_address(device_id, name, value) VALUES(187, 'ptmx_fops', '0xc1067b48');
  INSERT INTO device_address(device_id, name, value) VALUES(187, 'perf_swevent_enabled', '0xc1048d54');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(188, 'HTL21', 'JRO03C', 'ro.aa.romver', '1.39.970.3');
  INSERT INTO device_address(device_id, name, value) VALUES(188, 'prepare_kernel_cred', '0xc00abeac');
  INSERT INTO device_address(device_id, name, value) VALUES(188, 'commit_creds', '0xc00ab998');
  INSERT INTO device_address(device_id, name, value) VALUES(188, 'remap_pfn_range', '0xc00ff808');
  INSERT INTO device_address(device_id, name, value) VALUES(188, 'vmalloc_exec', '0xc010bc04');
  INSERT INTO device_address(device_id, name, value) VALUES(188, 'ptmx_fops', '0xc0d1df44');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(189, 'L-01F', 'JDQ39B', 'ro.lge.swversion', 'L01F11k');
  INSERT INTO device_address(device_id, name, value) VALUES(189, 'prepare_kernel_cred', '0xc00c37a8');
  INSERT INTO device_address(device_id, name, value) VALUES(189, 'commit_creds', '0xc00c329c');
  INSERT INTO device_address(device_id, name, value) VALUES(189, 'remap_pfn_range', '0xc0144c20');
  INSERT INTO device_address(device_id, name, value) VALUES(189, 'vmalloc_exec', '0xc01521dc');
  INSERT INTO device_address(device_id, name, value) VALUES(189, 'ptmx_fops', '0xc101c4d0');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(190, 'LGL22', 'JDQ39B', 'ro.lge.swversion', 'LGL2210a');
  INSERT INTO device_address(device_id, name, value) VALUES(190, 'prepare_kernel_cred', '0xc00c3894');
  INSERT INTO device_address(device_id, name, value) VALUES(190, 'commit_creds', '0xc00c3388');
  INSERT INTO device_address(device_id, name, value) VALUES(190, 'remap_pfn_range', '0xc0144d10');
  INSERT INTO device_address(device_id, name, value) VALUES(190, 'vmalloc_exec', '0xc01522cc');
  INSERT INTO device_address(device_id, name, value) VALUES(190, 'ptmx_fops', '0xc101a7a0');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(191, 'LGL22', 'JDQ39B', 'ro.lge.swversion', 'LGL2210b');
  INSERT INTO device_address(device_id, name, value) VALUES(191, 'prepare_kernel_cred', '0xc00c3adc');
  INSERT INTO device_address(device_id, name, value) VALUES(191, 'commit_creds', '0xc00c35d0');
  INSERT INTO device_address(device_id, name, value) VALUES(191, 'remap_pfn_range', '0xc0145038');
  INSERT INTO device_address(device_id, name, value) VALUES(191, 'vmalloc_exec', '0xc01525f4');
  INSERT INTO device_address(device_id, name, value) VALUES(191, 'ptmx_fops', '0xc101a7a0');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(192, 'LGL23', 'JDQ39B', 'ro.lge.swversion', 'LGL2310d');
  INSERT INTO device_address(device_id, name, value) VALUES(192, 'prepare_kernel_cred', '0xc00c2e58');
  INSERT INTO device_address(device_id, name, value) VALUES(192, 'commit_creds', '0xc00c294c');
  INSERT INTO device_address(device_id, name, value) VALUES(192, 'remap_pfn_range', '0xc01442d4');
  INSERT INTO device_address(device_id, name, value) VALUES(192, 'vmalloc_exec', '0xc0151890');
  INSERT INTO device_address(device_id, name, value) VALUES(192, 'ptmx_fops', '0xc111fba0');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(193, 'GT-I9195', 'JDQ39.I9195XXUAMF5', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(193, 'prepare_kernel_cred', '0xc009b798');
  INSERT INTO device_address(device_id, name, value) VALUES(193, 'commit_creds', '0xc009b284');
  INSERT INTO device_address(device_id, name, value) VALUES(193, 'remap_pfn_range', '0xc010c818');
  INSERT INTO device_address(device_id, name, value) VALUES(193, 'vmalloc_exec', '0xc0119104');
  INSERT INTO device_address(device_id, name, value) VALUES(193, 'ptmx_fops', '0xc0f26100');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(194, '201K','117.1.1c00', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(194, 'prepare_kernel_cred', '0xc008dab4');
  INSERT INTO device_address(device_id, name, value) VALUES(194, 'commit_creds', '0xc008d5a0');
  INSERT INTO device_address(device_id, name, value) VALUES(194, 'ptmx_fops', '0xc0f17a60');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(195, 'P-03E', '10.1010', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(195, 'prepare_kernel_cred', '0xc00a50f4');
  INSERT INTO device_address(device_id, name, value) VALUES(195, 'commit_creds', '0xc00a4c18');
  INSERT INTO device_address(device_id, name, value) VALUES(195, 'remap_pfn_range', '0xc011bcfc');
  INSERT INTO device_address(device_id, name, value) VALUES(195, 'vmalloc_exec', '0xc01281a0');
  INSERT INTO device_address(device_id, name, value) VALUES(195, 'ptmx_fops', '0xc11b3574');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(196, 'P-02E', '10.0818', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(196, 'prepare_kernel_cred', '0xc009b93c');
  INSERT INTO device_address(device_id, name, value) VALUES(196, 'commit_creds', '0xc009b460');
  INSERT INTO device_address(device_id, name, value) VALUES(196, 'ptmx_fops', '0xc0f72ba4');
  INSERT INTO device_address(device_id, name, value) VALUES(196, 'remap_pfn_range', '0xc0110324');
  INSERT INTO device_address(device_id, name, value) VALUES(196, 'vmalloc_exec', '0xc011c7c8');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(197, '202K', '101.0.2c10', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(197, 'prepare_kernel_cred', '0xc009e3d0');
  INSERT INTO device_address(device_id, name, value) VALUES(197, 'commit_creds', '0xc009debc');
  INSERT INTO device_address(device_id, name, value) VALUES(197, 'ptmx_fops', '0xc0f469f8');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(198, 'SH-01E', '02.00.02', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(198, 'prepare_kernel_cred', '0xc008bb78');
  INSERT INTO device_address(device_id, name, value) VALUES(198, 'commit_creds', '0xc008b6a4');
  INSERT INTO device_address(device_id, name, value) VALUES(198, 'ptmx_fops', '0xc0dd44f0');
  INSERT INTO device_address(device_id, name, value) VALUES(198, 'remap_pfn_range', '0xc00e26a4');
  INSERT INTO device_address(device_id, name, value) VALUES(198, 'vmalloc_exec', '0xc00ef1ec');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(199, 'Nexus 5', 'KTU84P', 'gsm.version.baseband', 'M8974A-2.0.50.1.16');
  INSERT INTO device_address(device_id, name, value) VALUES(199, 'prepare_kernel_cred', '0xc01bb44c');
  INSERT INTO device_address(device_id, name, value) VALUES(199, 'commit_creds', '0xc01bac5c');
  INSERT INTO device_address(device_id, name, value) VALUES(199, 'ptmx_fops', '0xc1235dd0');
  INSERT INTO device_address(device_id, name, value) VALUES(199, 'remap_pfn_range', '0xc024dafc');
  INSERT INTO device_address(device_id, name, value) VALUES(199, 'vmalloc_exec', '0xc025a0f8');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(200, 'LGL22', 'KOT49I', 'ro.lge.swversion', 'LGL2220d');
  INSERT INTO device_address(device_id, name, value) VALUES(200, 'prepare_kernel_cred', '0xc01c65e8');
  INSERT INTO device_address(device_id, name, value) VALUES(200, 'commit_creds', '0xc01c6098');
  INSERT INTO device_address(device_id, name, value) VALUES(200, 'ptmx_fops', '0xc12532a0');
  INSERT INTO device_address(device_id, name, value) VALUES(200, 'remap_pfn_range', '0xc0251abc');
  INSERT INTO device_address(device_id, name, value) VALUES(200, 'vmalloc_exec', '0xc025f168');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(201, '204HW', 'Y300-J1V100R001C111B121', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(201, 'prepare_kernel_cred', '0xc00bd3a8');
  INSERT INTO device_address(device_id, name, value) VALUES(201, 'commit_creds', '0xc00bcfe0');
  INSERT INTO device_address(device_id, name, value) VALUES(201, 'ptmx_fops', '0xc0b0b130');

INSERT INTO supported_devices(device_id, device, build_id, check_property_name, check_property_value) VALUES(202, 'F-05E', 'V11R35A', NULL, NULL);
  INSERT INTO device_address(device_id, name, value) VALUES(202, 'ptmx_fops', '0xc0b1e948');
  INSERT INTO device_address(device_id, name, value) VALUES(202, 'prepare_kernel_cred', '0xc0090d78');
  INSERT INTO device_address(device_id, name, value) VALUES(202, 'commit_creds', '0xc0090734');
  INSERT INTO device_address(device_id, name, value) VALUES(202, 'remap_pfn_range', '0xc00e2064');


COMMIT;
