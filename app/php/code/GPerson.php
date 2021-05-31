<?php
class GPerson {
    //===============================================
    private $name;
    private $code;
    private $coef;
    //===============================================
    public function __construct($name, $code, $coef) {
        $this->name = $name;
        $this->code = $code;
        $this->coef = $coef;
    }
    //===============================================
    public function print() {
        echo sprintf("Person[Nom] : %s<br/>\n", $this->name);
        echo sprintf("Person[Code] : %d<br/>\n", $this->code);
        echo sprintf("Person[Coef] : %.2f<br/>\n", $this->coef);
    }
    //===============================================
}
?>
