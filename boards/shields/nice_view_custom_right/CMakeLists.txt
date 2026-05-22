# Copyright (c) 2023 The ZMK Contributors
# SPDX-License-Identifier: MIT

if(CONFIG_SHIELD_NICE_VIEW_CUSTOM_RIGHT)
  zephyr_library()
  zephyr_library_sources(widgets/art.c)
  zephyr_library_sources(widgets/peripheral_status.c)
  zephyr_library_sources(widgets/bolt.c)
  zephyr_library_sources(widgets/util.c)
  zephyr_library_sources_ifdef(CONFIG_ZMK_SPLIT_ROLE_CENTRAL widgets/status.c)
  zephyr_library_include_directories(widgets)
endif()
