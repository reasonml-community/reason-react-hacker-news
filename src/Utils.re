/* require css file for side effect only */
external requireCSS : string => unit = "require" [@@bs.val];

/* require an asset (eg. an image) and return exported string value (image URI) */
external requireAssetURI : string => string = "require" [@@bs.val];

/* format a timestamp in seconds as relative humanised time sentence */
external fromNow : int => string = "fromNow" [@@bs.module "src/UtilsJS"];

external internal_getAttribute : Js.t 'a => string => Js.null string =
  "getAttribute" [@@bs.module "src/UtilsJS"];

let getAttribute node name => Js.Null.to_opt (internal_getAttribute node name);

external dangerousHtml : string => Js.t 'a = "dangerousHtml" [@@bs.module "src/UtilsJS"];

let intEl n => ReactRe.stringToElement (string_of_int n);

let textEl str => ReactRe.stringToElement str;
