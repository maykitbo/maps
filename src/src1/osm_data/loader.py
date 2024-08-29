import overpass
import geojson


def get_data_from_overpass(south, west, north, east):
    api = overpass.API(timeout=500)

    return api.get(f"""
        node({south}, {west}, {north}, {east});
        way({south}, {west}, {north}, {east});
        (._;>;)
    """, verbosity='geom')



if __name__ == '__main__':
    # Read description.txt and store the data in a set
    desc = set()
    try:
        with open('description.txt', 'r') as file:
            for line in file:
                parts = line.strip().split()
                bbox = tuple(map(float, parts[1:5]))  # Extract bbox coordinates
                desc.add(bbox)
    except FileNotFoundError:
        print("description.txt not found. Creating a new one.")
        open('description.txt', 'w').close()


    bboxes = [
    #   south    west    north   east
        (55.810, 37.660, 55.812, 37.666),
        (55.809, 37.655, 55.813, 37.666),
        (55.809, 37.650, 55.814, 37.666),
        (55.805, 37.650, 55.814, 37.666),
        (55.800, 37.645, 55.812, 37.666)
    ]



    for idx, bbox in enumerate(bboxes):
        if bbox not in desc:

            south, west, north, east = bbox

            # get data from overpass api
            data = get_data_from_overpass(south, west, north, east)
            
            # save data as geo.json
            filename = f'osm_{idx}.geo.json'
            with open(filename, mode="w") as f:
                geojson.dump(data, f, indent=1)

            features_count = len(data['features'])
                    
            # Update description.txt and desc set
            with open('description.txt', 'a') as file:
                file.write(f"{idx} {south} {west} {north} {east} {features_count}\n")
            
            print(f"OSM data for bbox {bbox} has been saved to {filename}")

    print("All new OSM data has been processed and saved.")



