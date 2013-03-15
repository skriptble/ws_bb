<?php

class Blueprint_Parser {
  /*********************
  ***Class Properties***
  **********************/
  private $lorem_ipsum = "<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque molestie ullamcorper mollis. Aenean enim erat, volutpat eu egestas a, vestibulum id neque. Sed malesuada, lacus quis lacinia adipiscing, augue lacus faucibus tellus, a tempus tortor mauris ornare massa. Vivamus dignissim ligula ut arcu scelerisque sed laoreet ipsum iaculis. Duis feugiat volutpat ante vel accumsan. Etiam in rhoncus justo. Fusce non ligula nibh. Quisque tellus massa, rutrum et ullamcorper at, luctus ac nisl. Mauris facilisis sapien et lectus rutrum vel varius elit molestie. Quisque sit amet libero nisi, sit amet dictum nisl. Maecenas tristique enim eget nibh dictum iaculis eget ac tellus. Aenean dapibus, risus eget scelerisque placerat, orci tellus accumsan orci, a vestibulum est orci sed lorem. Praesent eleifend egestas massa, elementum cursus sapien aliquam at.</p><p>Ut metus leo, rhoncus nec blandit vitae, auctor non turpis. Vestibulum sapien libero, lobortis eget scelerisque non, vehicula sed mauris. Aenean sit amet sollicitudin massa. Suspendisse potenti. Suspendisse ligula nibh, volutpat vitae porttitor egestas, vehicula quis diam. Mauris convallis arcu vel dolor gravida non cursus elit hendrerit. Mauris vitae venenatis tortor. Pellentesque venenatis dignissim tortor, ut egestas lorem sagittis vitae. Suspendisse nec ante felis, sed dictum ante. Nullam turpis leo, blandit a condimentum quis, hendrerit eu mi. Vivamus vestibulum mauris et neque mattis euismod. Praesent in ultrices magna. Proin laoreet velit id dui venenatis ut iaculis enim convallis. Duis porttitor, dolor vel ornare adipiscing, ante nisi fermentum quam, nec lobortis nibh mi ac lectus.</p>";
  private $xml_dir;
  public $xml_file;
  public $entries = array();  
  public $rand_array = array();
  public function __construct() {
         $this->xml_dir = variable_get('ws_bb_xml_directory', 'public://wb_ss/xml');
    }
  
  public function parse(stdClass $blueprint) {
    $blueprint_uri = $blueprint->uri;
    $simple = '<doc>' . file_get_contents($blueprint_uri) . '</doc>';
    $this->scrub_text($simple);
    $this->replace_tabs($simple);
    $parser = xml_parser_create();
    xml_parse_into_struct($parser, $simple, $vals, $index);
    xml_parser_free($parser);

    $blueprint_val_index = $index['BLUEPRINT'][0];

    $this->entries = explode("\n", $vals[$blueprint_val_index]['value']);
    print_r($this->entries);
    return $vals[$blueprint_val_index];
    
  }
  
  /**
   * Builds an XML file from the blueprint array created by the parse function
   * 
   *
   * @param $blueprint
   *  An array containing the strings from the blueprint file
   *
   * @param $base_directory
   *  The file containing the extracted blueprint files
   *
   * @param $site_name
   *  The name of the site
   *
   * @param $menu_name
   *  The menu to be used for the imported pages
   */
  
  public function sitemap_converter($blueprint, $base_directory, $site_name, $menu_name = 'main-menu') {
    $xml = array();

   foreach($blueprint as $entry_str) {
      $entry = explode(' ', $entry_str, 2);
      if(empty($entry[0])) continue;
      list($id, $name) = $entry;
    
      $this->clean_titles($name);
      if (trim($id) == '') continue; // continue of the id is empty
      $xml[$id] = array(
        'title' => $name,
        'machine' => $this->machine_conversion($name),
      );
      $xml[$id]['path'] = $this->create_path($id, $xml);
      $xml[$id]['page-content'] = $this->get_page_contents($base_directory, $name);
    }
  
    $date = date('MdY', time());
    $xml_file = $this->xml_dir . "$site_name.$date.blueprint.xml";
   # // Deleting the file if it exists to avoid malformed XML issue.
   # if(file_exists($xml_file)) { unlink($xml_file); print 'unlinked'; }
   # $fh = fopen($xml_file, 'w') or die("can't open file");
  
    $string = '<?xml version="1.0"?><blueprint>';
  
    foreach($xml as $menu_router) {
      $string .= '<page><title>' . trim($this->format_name($menu_router['title'])) . '</title>';
      $string .= '<content>' . $menu_router['page-content'] . '</content>';
      $string .= '<path>' . $menu_router['path'] . '</path>';
      $string .= '<menu_name>' . $menu_name . '</menu_name></page>';
    }
    $string .= '</blueprint>';

    $destination_root = "public://ws_bb/xml";
    file_prepare_directory($destination_root, FILE_CREATE_DIRECTORY);
    file_unmanaged_save_data($string,"public://ws_bb/xml/$site_name.$date.blueprint.xml", FILE_EXISTS_REPLACE);
    $this->xml_file = "public://ws_bb/xml/$site_name.$date.blueprint.xml";

  }
  
  /**********************
  ***Utility Functions***
  ***********************/  
  /**
   * Replaces the tabs in a string (by reference) with spaces.
   * This function will account for an entry with a trailing . (1.1.)
   *
   * @param $string
   *  The string to modify
   *
   * @return
   *  The string with tabs replaced by spaces
   */
  protected function replace_tabs(&$string) {
    if(strpos($string, '.	')) {
    $string = str_replace('.	', ' ', $string);
    } else {
    $string = str_replace('	', ' ', $string);
    }
  }
  
  /**
   * Cleans up a string and removes characters that will cause the XML parser to fail
   *
   * @param $string
   *  The string to modify
   *
   * @return
   *  The string with characters swapped with words or nothing.
   */
  protected function scrub_text(&$string) {
    $string = str_replace("&", "and", $string);
  }  
  
  public function clean_titles(&$string) {
    preg_match('/(?P<string>[\w\s-]+)/', $string, $matches);
    $string = $matches ? $matches['string'] : '';
  }
  /**
   * Takes a string, converts it into an array, and creates an XML document from it.
   *
   * @param $blueprint
   *  An array containing the sitemap entries to create.
   */
  
  /**********************************
  ********Conversion Library*********
  ***********************************/
  
  /**
  * Converts a string to lower case, replaces all spaces with hyphens, and converts
  * all other characters using htmlspecialchars.
  */
  public function machine_conversion($string) {
    $lowerstr = strtolower($string);
    $trimmed = trim($lowerstr);
    $text = str_replace(' ', '-', $trimmed);
    $str = preg_replace('/[^a-z\d\- ]/i', '', $text);
    $machine = str_replace(' ','',$str);
    return $machine;
  }
  
  public function format_name($string) {
    $str = preg_replace('/[^a-zA-Z0-9 ]/i', '', $string);
    return $str;
  }
  /**
  * Creates a path for a file from the ID and XML file.
  * If the item is at the top level it returns the machine, if it is a subpage,
  * it will return the machine name attached to the parent's path.
  *
  * @param $id
  *   The ID of the item.
  *
  * @param $xml
  *    The XML file constructed so far.
  *
  * @return
  *    The menu path.
  */
  public function create_path($id, $xml) {
    $menu_item = $xml[$id]['machine'];
    $id_arr = explode('.', $id);
    #print_r($xml);
  
    if(count($id_arr) <= 1) {
      return $menu_item;
    }
    
    array_pop($id_arr);
    $parent_id = implode('.', $id_arr);
    $parent_path = $xml[$parent_id]['path'];
    $path = $parent_path . '/' . $menu_item;
  
    return $path;
  }
  /**
  * Gets the contents for a page. Will look for a file with the same name as the title in
  * the pages directory. If not page is found, lorem ipsum is generated.
  *
  * @param $base_directory
  *   The root directory for this sitemap package.
  *
  * @param $title
  *    The page title.
  *
  * @return
  *    A string containing the page contents or lorem ipsum, both wrapped in <p> tags.
  */
  public function get_page_contents($base_directory, $title) {
    $pages_dir = $base_directory . '/pages/';
    $file_name = $pages_dir . trim($title) . '.txt';
    if(file_exists($file_name) && $this->extract_body($file_name)) {
      return $this->extract_body($file_name);
    }
    return $this->lorem_ipsum;
  }	
  
  /**
  * Returns the text inside of the "====Body" and "======" tags.
  *
  * @param $file
  *   The file to parse.
  *
  *
  * @return
  *    The body wrapped in <p> tags.
  */
  public function extract_body($file) {
    $items = array();
    $fh = fopen($file, 'r');
    $process = FALSE;
      while(!feof($fh)) {  						
        $raw_item = fgets($fh);
        if(trim($raw_item) == '======') $process = FALSE;
        if($process) {
          $items[] = $this->add_paragraph_tags($raw_item);
        }
        if(trim($raw_item) == '=====Body') $process = TRUE;  						
      }
    $body = implode('', $items);
    if(empty($body)) return FALSE;
    return $body;
  }
  
  /**
  * Adds paragraph tags to the given string.
  *
  * @param $string
  *   The string to be wrapped.
  *
  * @return
  *    A string wrapped in paragraph tags.
  */
  public function add_paragraph_tags($string) {
    return "<p>$string</p>";
  }
}
