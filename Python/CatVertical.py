import cv2

''' 
Reads an array of .png frames in read_dir and stacks vertically, compresses to .jpg and writes to write_dir
uses_name_padding = True uses Blender naming e.g. "0001.png"
name_start_index = 1 will start at "0001.png"
'''
def CatVertical(read_dir, num_images, write_name, write_dir = "", uses_name_padding = True, name_start_index = 0):
    if write_dir == "":
        write_dir = read_dir

    output_column = []

    print("Concatenating...")
    for image_pos in range(name_start_index, num_images + name_start_index):
        if uses_name_padding:
            image_id = str(image_pos).rjust(4, "0")
        else:
            image_id = str(image_pos)

        image_dir = read_dir + image_id + ".png"
        image = cv2.imread(image_dir)
        output_column.append(image)

    output_image = cv2.vconcat(output_column)

    print("Writing...")
    cv2.imwrite(write_dir + write_name + ".jpg", output_image, [cv2.IMWRITE_JPEG_QUALITY, 90])

    print("Done.")


if __name__ == '__main__':
    CatVertical("/Users/willcassidy/Development/GitHub/BlenderToJUCE/Blender/Dial Output/",
                25,
                "dial_image_sheet",
                "/Users/willcassidy/Development/GitHub/BlenderToJUCE/Blender/Dial Output/",
                True,
                1)