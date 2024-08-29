import json
from tqdm import tqdm
import overpy


def split_bbox(south, west, north, east, step):
    """Split the bbox into smaller sub-bboxes."""
    lat_steps = int((north - south) / step) + 1
    lon_steps = int((east - west) / step) + 1
    bboxes = []
    for i in range(lat_steps):
        for j in range(lon_steps):
            sub_south = south + i * step
            sub_north = min(south + (i + 1) * step, north)
            sub_west = west + j * step
            sub_east = min(west + (j + 1) * step, east)
            bboxes.append((sub_south, sub_west, sub_north, sub_east))
    return bboxes


def get_data_from_overpass(south, west, north, east):
    pass


def save_data_and_update_description(bboxes, desc_file='description.txt', step=0.1):
    for idx, bbox in enumerate(tqdm(bboxes, desc="Processing Bboxes")):
        south, west, north, east = bbox

        # # Get data from Overpass API
        data = get_data_from_overpass(south, west, north, east)
        
        
        # # Save data as OSM
        filename = f'osm_{idx}.osm'
        with open(filename, mode="w") as f:
            f.write(xml_data)
        
        # Update description.txt and desc set
        with open(desc_file, 'a') as file:
            file.write(f"{idx} {south} {west} {north} {east}\n")
        
        print(f"OSM data for bbox {bbox} has been saved to {filename}")

    print("All new OSM data has been processed and saved.")


if __name__ == '__main__':
    south, west, north, east = 41.00, 36.15, 56.50, 56.28
    step = 0.01
    bboxes = split_bbox(south, west, north, east, step)
    save_data_and_update_description(bboxes, step=step)




