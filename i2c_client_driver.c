/*
Linux i2c client driver implementation.
Current code is not specific to any chipset or vendor.
Code needs modification as per target client device
and is not expected to work as is for any chipset.
Below code provides a working and tested template to someone 
who would like to reuse this code and make changes to fit his/her needs.
*/
/*
1) Registers as i2c client driver
2) Probe routine is called by Linux subsystem when interested device Ids 
are enumerated.
3) sysfs interface - exposing something to user space, critical data
4) Kobject read write attributes, shown as files
5) 
*/
#include<linux/module.h> // included for all kernel modules
#include <linux/kernel.h> // included for KERN_INFO
#include <linux/init.h> // included for __init and __exit macros
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/slab.h>
#include <linux/list.h>

struct i2c_data_struct {
	struct device *hwmon_dev;
	struct mutex update_lock;

	u8 control;
	u8 aout;
};

static int i2c_sensor_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	printk("adapter name : [%s]\r\n"	,client->adapter->name);
	printk("device name  : [%s]\r\n"	,client->name);
	printk("addr 		 : [0x%X]\r\n"	,client->addr);
	
/*
	struct i2c_data_struct *data;
	int err;

	data = devm_kzalloc(&client->dev, sizeof(struct i2c_data_struct), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);
*/
	/* Initialize the PCF8591 chip */


	return 0;
}

static int i2c_sensor_remove(struct i2c_client *client)
{
	struct i2c_data_struct *data;
	int err;
/*
	data = devm_kzalloc(&client->dev, sizeof(struct i2c_data_struct), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);
*/
	/* Initialize the PCF8591 chip */


	return 0;
}



static const struct of_device_id i2c_sensor_of_matches[] = {
	{.compatible = "company,i2c_sensor",},
	{}
};
MODULE_DEVICE_TABLE(of, i2c_sensor_of_matches);

static const struct i2c_device_id i2c_sensor_id[] = {
    { "i2c_sensor", 0 },
    {}
};
MODULE_DEVICE_TABLE(i2c, i2c_sensor_id);

static struct i2c_driver i2c_sensor_driver = {
    .driver = {
        .name	= "i2c_sensor",
//		.pm 	= &i2c_sensor_pm_ops,	/* optional */
		.of_match_table = of_match_ptr(i2c_sensor_of_matches),
    },
    .probe        = i2c_sensor_probe,
    .remove       = i2c_sensor_remove,
    .id_table     = i2c_sensor_id,
  //  .address_list = normal_i2c,
};

//module_i2c_driver(i2c_sensor_driver);

static int __init i2c_client_module_init(void)
{
	printk("init I2C Module\r\n");
    return i2c_add_driver(&i2c_sensor_driver);
}

static void __exit i2c_client_module_exit(void)
{
	printk("exit I2C Module\r\n");
    i2c_del_driver(&i2c_sensor_driver);
}

MODULE_AUTHOR("Jaeson  <djs6421@qucell.com>");
MODULE_DESCRIPTION("i2c client driver");

module_init(i2c_client_module_init);
module_exit(i2c_client_module_exit);
