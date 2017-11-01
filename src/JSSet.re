type set('a) =
  | JSSet('a);

[@bs.new] external empty : unit => set('a) = "Set";

[@bs.send] external add : (set('a), 'a) => set('a) = "add";

[@bs.send] external delete_internal : (set('a), 'a) => unit = "delete";

[@bs.send] external has_internal : (set('a), 'a) => Js.boolean = "has";

let has = (s, v) => Js.to_bool(has_internal(s, v));

let remove = (s, v) => {
  delete_internal(s, v);
  s
};

let create = (values: array('a)) => {
  let empty_set = empty();
  Array.fold_left(add, empty_set, values)
};
