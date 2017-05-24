type set 'a =
  | JSSet 'a;

external empty : unit => set 'a = "Set" [@@bs.new];

external add : set 'a => 'a => set 'a = "add" [@@bs.send];

external delete_internal : set 'a => 'a => unit = "delete" [@@bs.send];

external has_internal : set 'a => 'a => Js.boolean = "has" [@@bs.send];

let has s v => Js.to_bool (has_internal s v);

let remove s v => {
  delete_internal s v;
  s
};

let create (values: array 'a) => {
  let empty_set = empty ();
  Array.fold_left add empty_set values
};
