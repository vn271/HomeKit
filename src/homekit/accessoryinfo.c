/*
 * accessoryinfo.c
 *
 *  Created on: Jun 8, 2015
 *      Author: tim
 */

#include <string.h>

#include <ble.h>
#include <ble_gatts.h>
#include <app_error.h>
#include <nordic_common.h>

#include "homekit-config.h"
#include "uuids.h"
#include "accessoryinfo.h"
#include "service.h"


static void accessoryinfo_identify(uint8_t* data, uint16_t length, const service_characteristic_t* characteristic)
{
  HOMEKIT_CONFIG_IDENTIFY_FUNCTION(data, length, ctx);
}

void accessoryinfo_init(void)
{
  static const service_service_t service =
  {
    .uuid = { .type = BLE_UUID_TYPE_BLE, .uuid = HOMEKIT_SERVICE_UUID_ACCESSORY_INFO }
  };
  static const service_characteristic_t characteristics[] =
  {
    { .name = "Service Instance ID", .uuid = { .type = HOMEKIT_BASE_TYPE, .uuid = HOMEKIT_SERVICE_ID }, .length = sizeof(HOMEKIT_CONFIG_SERVICE_ID) - 1, .ctx = HOMEKIT_CONFIG_SERVICE_ID, .read = service_read_string, .plain = 1 },
    { .name = "Identify", .uuid = { .type = HOMEKIT_BASE_TYPE, .uuid = HOMEKIT_IDENTITY }, .length = 1, .write = accessoryinfo_identify },
    { .name = "Manufacturer Name", .uuid = { .type = HOMEKIT_BASE_TYPE, .uuid = HOMEKIT_MANUFACTURER }, .length = sizeof(HOMEKIT_CONFIG_MANUFACTURER) - 1, .ctx = HOMEKIT_CONFIG_MANUFACTURER, .read = service_read_string },
    { .name = "Model Name", .uuid = { .type = HOMEKIT_BASE_TYPE, .uuid = HOMEKIT_MODEL }, .length = sizeof(HOMEKIT_CONFIG_MODEL) - 1, .ctx = HOMEKIT_CONFIG_MODEL, .read = service_read_string },
    { .name = "Name", .uuid = { .type = HOMEKIT_BASE_TYPE, .uuid = HOMEKIT_NAME }, .length = sizeof(HOMEKIT_CONFIG_NAME) - 1, .ctx = HOMEKIT_CONFIG_NAME, .read = service_read_string },
    { .name = "Serial Number", .uuid = { .type = HOMEKIT_BASE_TYPE, .uuid = HOMEKIT_SERIAL_NR }, .length = sizeof(HOMEKIT_CONFIG_SERIAL_NR) - 1, .ctx = HOMEKIT_CONFIG_SERIAL_NR, .read = service_read_string },
    {}
  };
  service_addService(&service, characteristics);
}